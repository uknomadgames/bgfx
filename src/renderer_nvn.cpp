/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"


#if BGFX_CONFIG_RENDERER_NVN

#include <nn/vi.h>
#include <nvn/nvn.h>

#include <nvn/nvn_FuncPtrInline.h>
#include <nvn/nvn_FuncPtrImpl.h>
#include <bx/crtimpl.h>
#include <atomic>
#include <math.h>

extern "C"
{
	PFNNVNGENERICFUNCPTRPROC NVNAPIENTRY nvnBootstrapLoader(const char* name);
}

static const size_t g_CommandMemorySize = 512;
static const size_t g_ControlMemorySize = 512;
static const int    g_NumColorBuffers = 2;

namespace bgfx
{
	namespace nvn
	{

		static const size_t g_MinimumPoolSize = NVN_MEMORY_POOL_STORAGE_GRANULARITY;

		class MemoryPool
		{
		public:
			MemoryPool() 
				: m_CurrentWriteOffset(0)
				, m_pMemory(nullptr)
				, m_allocator(nullptr)
				, m_Size(0)
			{
			}

			~MemoryPool()
			{
				if (m_pMemory != nullptr)
				{
					Shutdown();
				}
			}
			
			inline size_t GetSize() const
			{
				return m_Size;
			}

			static size_t Align(size_t size, size_t alignment)
			{
				size_t temp = (alignment - (size % alignment)) % alignment;

				return temp + size;
			}

			void Init(bx::AllocatorI *i_allocator, size_t size, int flags, NVNdevice* pDevice)
			{
				BX_CHECK(m_allocator == nullptr, "Already initialised");
				BX_CHECK(i_allocator != nullptr, "NULL Allocator");

				m_allocator = i_allocator;

				if (size < g_MinimumPoolSize)
				{
					/* Set memory pool to minimum allowed size */
					size = g_MinimumPoolSize;
				}

				m_Size = Align(size, NVN_MEMORY_POOL_STORAGE_GRANULARITY);
				m_pMemory = BX_ALIGNED_ALLOC(m_allocator, m_Size, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);


				NVNmemoryPoolBuilder poolBuilder;
				nvnMemoryPoolBuilderSetDefaults(&poolBuilder);
				nvnMemoryPoolBuilderSetDevice(&poolBuilder, pDevice);
				nvnMemoryPoolBuilderSetFlags(&poolBuilder, flags);
				nvnMemoryPoolBuilderSetStorage(&poolBuilder, m_pMemory, m_Size);

				if (nvnMemoryPoolInitialize(&m_MemoryPool, &poolBuilder) == NVN_FALSE)
				{
					BX_CHECK(0, "Failed to initialize buffer memory pool");
				}

				m_Flags = flags;
			}

			void Shutdown()
			{
				if (m_pMemory != NULL)
				{
					m_Size = 0;
					m_CurrentWriteOffset.store(0);

					nvnMemoryPoolFinalize(&m_MemoryPool);

					BX_ALIGNED_FREE(m_allocator, m_pMemory, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
					m_pMemory = NULL;
				}
			}

			ptrdiff_t GetNewMemoryChunkOffset(size_t size, size_t alignment)
			{
				if (static_cast<size_t>(m_CurrentWriteOffset.load()) >= m_Size)
				{
					BX_CHECK(0, "Memory pool out of memory.");
				}

				m_CurrentWriteOffset.store(Align(m_CurrentWriteOffset.load(), alignment));

				ptrdiff_t dataOffset = m_CurrentWriteOffset.load();

				m_CurrentWriteOffset.fetch_add(size);

				return dataOffset;
			}

			NVNmemoryPool* GetMemoryPool()
			{
				return &m_MemoryPool;
			}

		private:
			std::atomic<ptrdiff_t>      m_CurrentWriteOffset;
			NVNmemoryPool               m_MemoryPool;
			void*                       m_pMemory;
			bx::AllocatorI*				m_allocator;
			size_t                      m_Size;
			int                         m_Flags;
		};

		struct RendererContextNVN : public RendererContextI
		{
			RendererContextNVN()
			{
				m_pWindow = nullptr;
				m_Resolution.m_height = 0;
				m_Resolution.m_width = 0;
				m_CurrentWindowIndex = -1;
				for (int i = 0; i < g_NumColorBuffers; ++i)
				{
					m_RenderTargets[i] = NULL;
				}

				//////////////////////////////////////////////////////////////////////////
				m_pRenderTargetMemoryPool;

				// Pretend all features are available.
				g_caps.supported = 0
					| BGFX_CAPS_ALPHA_TO_COVERAGE
					| BGFX_CAPS_BLEND_INDEPENDENT
					| BGFX_CAPS_COMPUTE
					| BGFX_CAPS_CONSERVATIVE_RASTER
					| BGFX_CAPS_DRAW_INDIRECT
					| BGFX_CAPS_FRAGMENT_DEPTH
					| BGFX_CAPS_FRAGMENT_ORDERING
					| BGFX_CAPS_GRAPHICS_DEBUGGER
					| BGFX_CAPS_HIDPI
					| BGFX_CAPS_HMD
					| BGFX_CAPS_INDEX32
					| BGFX_CAPS_INSTANCING
					| BGFX_CAPS_OCCLUSION_QUERY
					| BGFX_CAPS_RENDERER_MULTITHREADED
					| BGFX_CAPS_SWAP_CHAIN
					| BGFX_CAPS_TEXTURE_2D_ARRAY
					| BGFX_CAPS_TEXTURE_3D
					| BGFX_CAPS_TEXTURE_BLIT
					| BGFX_CAPS_TEXTURE_COMPARE_ALL
					| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
					| BGFX_CAPS_TEXTURE_CUBE_ARRAY
					| BGFX_CAPS_TEXTURE_READ_BACK
					| BGFX_CAPS_VERTEX_ATTRIB_HALF
					| BGFX_CAPS_VERTEX_ATTRIB_UINT10
					;

				g_caps.limits.maxTextureSize = 16384;
				g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(16, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS));

				//TODO: Format support: Line 1198 of renderer_d3d12
			}

			~RendererContextNVN()
			{
			}

			RendererType::Enum getRendererType() const BX_OVERRIDE
			{
				return RendererType::NVN;
			}

			const char* getRendererName() const BX_OVERRIDE
			{
				return BGFX_RENDERER_NVN_NAME;
			}

			bool isDeviceRemoved() BX_OVERRIDE
			{
				return false;
			}

			void flip(HMD& /*_hmd*/) BX_OVERRIDE
			{
				int t = 10;
			}

			//////////////////////////////////////////////////////////////////////////

			void createIndexBuffer(IndexBufferHandle /*_handle*/, Memory* /*_mem*/, uint16_t /*_flags*/) BX_OVERRIDE
			{
			}

			void destroyIndexBuffer(IndexBufferHandle /*_handle*/) BX_OVERRIDE
			{
			}

			void createVertexDecl(VertexDeclHandle /*_handle*/, const VertexDecl& /*_decl*/) BX_OVERRIDE
			{
			}

			void destroyVertexDecl(VertexDeclHandle /*_handle*/) BX_OVERRIDE
			{
			}

			void createVertexBuffer(VertexBufferHandle /*_handle*/, Memory* /*_mem*/, VertexDeclHandle /*_declHandle*/, uint16_t /*_flags*/) BX_OVERRIDE
			{
			}

			void destroyVertexBuffer(VertexBufferHandle /*_handle*/) BX_OVERRIDE
			{
			}

			void createDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) BX_OVERRIDE
			{
			}

			void updateDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/) BX_OVERRIDE
			{
			}

			void destroyDynamicIndexBuffer(IndexBufferHandle /*_handle*/) BX_OVERRIDE
			{
			}

			void createDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) BX_OVERRIDE
			{
			}

			void updateDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/) BX_OVERRIDE
			{
			}

			void destroyDynamicVertexBuffer(VertexBufferHandle /*_handle*/) BX_OVERRIDE
			{
			}

			//////////////////////////////////////////////////////////////////////////

			void createShader(ShaderHandle /*_handle*/, Memory* /*_mem*/) BX_OVERRIDE
			{
				int t = 10;
			}

			void destroyShader(ShaderHandle /*_handle*/) BX_OVERRIDE
			{
			}

			void createProgram(ProgramHandle /*_handle*/, ShaderHandle /*_vsh*/, ShaderHandle /*_fsh*/) BX_OVERRIDE
			{
				int t = 10;
			}

			void destroyProgram(ProgramHandle /*_handle*/) BX_OVERRIDE
			{
			}

			//////////////////////////////////////////////////////////////////////////

			void createTexture(TextureHandle /*_handle*/, Memory* /*_mem*/, uint32_t /*_flags*/, uint8_t /*_skip*/) BX_OVERRIDE
			{
			}

			void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) BX_OVERRIDE
			{
			}

			void updateTexture(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/, const Rect& /*_rect*/, uint16_t /*_z*/, uint16_t /*_depth*/, uint16_t /*_pitch*/, const Memory* /*_mem*/) BX_OVERRIDE
			{
			}

			void updateTextureEnd() BX_OVERRIDE
			{
			}

			void readTexture(TextureHandle /*_handle*/, void* /*_data*/, uint8_t /*_mip*/) BX_OVERRIDE
			{
			}

			void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint8_t /*_numMips*/) BX_OVERRIDE
			{
			}

			void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/) BX_OVERRIDE
			{
			}

			uintptr_t getInternal(TextureHandle /*_handle*/) BX_OVERRIDE
			{
				return 0;
			}

			void destroyTexture(TextureHandle /*_handle*/) BX_OVERRIDE
			{
			}

			//////////////////////////////////////////////////////////////////////////

			void createFrameBuffer(FrameBufferHandle /*_handle*/, uint8_t /*_num*/, const Attachment* /*_attachment*/) BX_OVERRIDE
			{
			}

			void createFrameBuffer(FrameBufferHandle /*_handle*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_depthFormat*/) BX_OVERRIDE
			{
			}

			void destroyFrameBuffer(FrameBufferHandle /*_handle*/) BX_OVERRIDE
			{
			}
//////////////////////////////////////////////////////////////////////////

			void createUniform(UniformHandle /*_handle*/, UniformType::Enum /*_type*/, uint16_t /*_num*/, const char* /*_name*/) BX_OVERRIDE
			{
			}

			void destroyUniform(UniformHandle /*_handle*/) BX_OVERRIDE
			{
			}

			void requestScreenShot(FrameBufferHandle /*_handle*/, const char* /*_filePath*/) BX_OVERRIDE
			{
			}

			void updateViewName(uint8_t /*_id*/, const char* /*_name*/) BX_OVERRIDE
			{
			}

			void updateUniform(uint16_t /*_loc*/, const void* /*_data*/, uint32_t /*_size*/) BX_OVERRIDE
			{
			}

			void setMarker(const char* /*_marker*/, uint32_t /*_size*/) BX_OVERRIDE
			{
			}

			void invalidateOcclusionQuery(OcclusionQueryHandle /*_handle*/) BX_OVERRIDE
			{
			}

			void submit(Frame* _render, ClearQuad& /*_clearQuad*/, TextVideoMemBlitter& /*_textVideoMemBlitter*/) BX_OVERRIDE
			{
				//TODO: This is where we should "resize" our swapchain if required


				/* Check for the window being minimized or having no visible surface. */
				if (updateResolution(_render->m_resolution) 
					|| m_Resolution.m_width == 0 
					|| m_Resolution.m_height == 0)
				{
					return;
				}

				int index = UpdateRenderTargets();
				nvnSyncWait(&m_WindowSync, NVN_WAIT_TIMEOUT_MAXIMUM);

				/* Render target setting command buffer. */
				nvnQueueSubmitCommands(&m_Queue, 1, &m_RenderTargetCommandHandle);

				nvnQueueSubmitCommands(&m_Queue, 1, &m_CommandHandle);
				nvnQueuePresentTexture(&m_Queue, m_pWindow, index);
			}

			void blitSetup(TextVideoMemBlitter& /*_blitter*/) BX_OVERRIDE
			{
			}

			void blitRender(TextVideoMemBlitter& /*_blitter*/, uint32_t /*_numIndices*/) BX_OVERRIDE
			{
			}

			//////////////////////////////////////////////////////////////////////////

			int UpdateRenderTargets()
			{

				NVNwindowAcquireTextureResult result = nvnWindowAcquireTexture(
					m_pWindow, 
					&m_WindowSync, 
					&m_CurrentWindowIndex);

				BX_CHECK(result == NVN_WINDOW_ACQUIRE_TEXTURE_RESULT_SUCCESS, "");

				nvnQueueFenceSync(&m_Queue, &m_CommandBufferSync, NVN_SYNC_CONDITION_ALL_GPU_COMMANDS_COMPLETE, 0);
				nvnQueueFlush(&m_Queue);
				nvnSyncWait(&m_CommandBufferSync, NVN_WAIT_TIMEOUT_MAXIMUM);

				nvnCommandBufferAddCommandMemory(&m_RenderTargetCommandBuffer, m_pCommandMemoryPool->GetMemoryPool(), m_RenderTargetCommandPoolOffset, g_CommandMemorySize);
				nvnCommandBufferAddControlMemory(&m_RenderTargetCommandBuffer, m_pRenderTargetControlPool, g_ControlMemorySize);

				nvnCommandBufferBeginRecording(&m_RenderTargetCommandBuffer);
				nvnCommandBufferSetRenderTargets(&m_RenderTargetCommandBuffer, 1, &m_RenderTargets[m_CurrentWindowIndex], NULL, NULL, NULL);
				m_RenderTargetCommandHandle = nvnCommandBufferEndRecording(&m_RenderTargetCommandBuffer);

				/* Return the index acquired from the NVNwindow so it can be used in the next present call. */
				return m_CurrentWindowIndex;
			}

			bool updateResolution(Resolution const &i_resolution)
			{
				if (m_Resolution.m_width == i_resolution.m_width
					&& m_Resolution.m_height == i_resolution.m_height)
				{
					return false;
				}
				m_Resolution = i_resolution;

				nvnQueueFenceSync(&m_Queue, &m_CommandBufferSync, NVN_SYNC_CONDITION_ALL_GPU_COMMANDS_COMPLETE, 0);

				nvnQueueFlush(&m_Queue);
				nvnSyncWait(&m_CommandBufferSync, NVN_WAIT_TIMEOUT_MAXIMUM);

				if (m_pWindow == NULL)
				{
					m_pWindow = new NVNwindow;
				}
				else
				{
					nvnWindowFinalize(m_pWindow);
				}

				nvnTextureBuilderSetSize2D(
					&m_RenderTargetBuilder, 
					m_Resolution.m_width, 
					m_Resolution.m_height);

				for (int i = 0; i < g_NumColorBuffers; ++i)
				{
					/* If it's the first time Resize is called, allocate the texture. */
					if (!m_RenderTargets[i])
					{
						m_RenderTargets[i] = new NVNtexture;
					}
					else
					{
						nvnTextureFinalize(m_RenderTargets[i]);
					}

					nvnTextureBuilderSetStorage(
						&m_RenderTargetBuilder, 
						m_pRenderTargetMemoryPool->GetMemoryPool(), 
						m_ColorTargetSize * i);

					nvnTextureInitialize(m_RenderTargets[i], &m_RenderTargetBuilder);
				}

				nvnWindowBuilderSetTextures(&m_WindowBuilder, g_NumColorBuffers, m_RenderTargets);
				nvnWindowInitialize(m_pWindow, &m_WindowBuilder);


				/* Clear Colors */
				float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
				float   red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
				float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
				float  blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

				/* Temporary variables for size/position of cleared rects. */
				int halfWidth = static_cast<int>(ceil(m_Resolution.m_width / 2.0f));
				int halfHeight = static_cast<int>(ceil(m_Resolution.m_height / 2.0f));

				nvnCommandBufferAddCommandMemory(&m_CommandBuffer, m_pCommandMemoryPool->GetMemoryPool(), m_CommandPoolOffset, g_CommandMemorySize);
				nvnCommandBufferAddControlMemory(&m_CommandBuffer, m_pControlPool, g_ControlMemorySize);

				/* Starts the recording of a new set of commands for the given command buffer. */
				nvnCommandBufferBeginRecording(&m_CommandBuffer);
				{
					auto width = m_Resolution.m_width;
					auto height = m_Resolution.m_height;
					/*
					* Lower left quadrant - black
					* Sets the scissor rectangle by the coordinates of its lower left
					* and its width/height.
					*/
					nvnCommandBufferSetScissor(&m_CommandBuffer, 0, 0, halfWidth, halfHeight);

					/*
					* Clears the currently set render target at a given index.
					* Channels to be cleared are set through the clear color mask.
					*/
					nvnCommandBufferClearColor(&m_CommandBuffer, 0, black, NVN_CLEAR_COLOR_MASK_RGBA);

					/* Lower right quadrant - red */
					nvnCommandBufferSetScissor(&m_CommandBuffer, halfWidth, 0, width - halfWidth, halfHeight);
					nvnCommandBufferClearColor(&m_CommandBuffer, 0, red, NVN_CLEAR_COLOR_MASK_RGBA);

					/* Upper right quadrant - green */
					nvnCommandBufferSetScissor(&m_CommandBuffer, halfWidth, halfHeight, width - halfWidth, height - halfHeight);
					nvnCommandBufferClearColor(&m_CommandBuffer, 0, green, NVN_CLEAR_COLOR_MASK_RGBA);

					/* Upper left quadrant - blue */
					nvnCommandBufferSetScissor(&m_CommandBuffer, 0, halfHeight, halfWidth, height - halfHeight);
					nvnCommandBufferClearColor(&m_CommandBuffer, 0, blue, NVN_CLEAR_COLOR_MASK_RGBA);
				}
				m_CommandHandle = nvnCommandBufferEndRecording(&m_CommandBuffer);
				
				return true;
			}


			// static
			static void DebugLayerCallback(
				NVNdebugCallbackSource source,
				NVNdebugCallbackType type,
				int id,
				NVNdebugCallbackSeverity severity,
				const char* message,
				void* pUser
			)
			{
				BX_CHECK(pUser == NULL, "");

				BX_TRACE("NVN Debug Layer Callback:\n");
				BX_TRACE("  source:       0x%08x\n", source);
				BX_TRACE("  type:         0x%08x\n", type);
				BX_TRACE("  id:           0x%08x\n", id);
				BX_TRACE("  severity:     0x%08x\n", severity);
				BX_TRACE("  message:      %s\n", message);

				BX_CHECK(0, "NVN Debug layer callback hit");
			}

			bool init()
			{
				BX_TRACE("Begin NVN init");

				nn::vi::NativeWindowHandle const  nativeWindow =
					(nn::vi::NativeWindowHandle) g_platformData.nwh;

				BX_CHECK(nativeWindow != nullptr, "NativeWindow not set using bgfx::setPlatformData");
				BX_CHECK(nvnBootstrapLoader != NULL, "Bootstrap loader function pointer is NULL\n");

				pfnc_nvnDeviceInitialize = reinterpret_cast<PFNNVNDEVICEINITIALIZEPROC>((*nvnBootstrapLoader)("nvnDeviceInitialize"));
				pfnc_nvnDeviceGetProcAddress = reinterpret_cast<PFNNVNDEVICEGETPROCADDRESSPROC>((*nvnBootstrapLoader)("nvnDeviceGetProcAddress"));
				if (!pfnc_nvnDeviceInitialize)
				{
					/* This can happen if an NVN driver is not installed on a Windows PC. */
					BX_CHECK(false, "BootstrapLoader failed to find nvnDeviceInitialize");
				}

				nvnLoadCProcs(NULL, pfnc_nvnDeviceGetProcAddress);

				int MajorVersion, MinorVersion;
				nvnDeviceGetInteger(NULL, NVN_DEVICE_INFO_API_MAJOR_VERSION, &MajorVersion);
				nvnDeviceGetInteger(NULL, NVN_DEVICE_INFO_API_MINOR_VERSION, &MinorVersion);

				BX_TRACE("NVN Major: %d", MajorVersion);
				BX_TRACE("NVN Minor: %d", MinorVersion);

				if (MajorVersion != NVN_API_MAJOR_VERSION || MinorVersion < NVN_API_MINOR_VERSION)
				{
					BX_CHECK(0, "NVN SDK not supported by current driver.");
				}

				/* If debug or develop is enabled, turn on NVN's debug layer. */
				int deviceFlags = 0;
#if defined(BGFX_CONFIG_DEBUG) 
				deviceFlags = NVN_DEVICE_FLAG_DEBUG_ENABLE_BIT;
#endif

				NVNdeviceBuilder deviceBuilder;
				nvnDeviceBuilderSetDefaults(&deviceBuilder);
				nvnDeviceBuilderSetFlags(&deviceBuilder, deviceFlags);

				if (nvnDeviceInitialize(&m_Device, &deviceBuilder) == false)
				{
					/*
					* This can fail for a few reasons; the most likely on Horizon is
					* insufficient device memory.
					*/
					BX_CHECK(false, "nvnDeviceInitialize");
				}
				BX_TRACE("NVN device initialised");

				nvnLoadCProcs(&m_Device, pfnc_nvnDeviceGetProcAddress);

				/*
				* Debug Layer Callback
				* --------------------
				* Install the debug layer callback if the debug layer was enabled during
				* device initialization. It is possible to pass a pointer to the NVN API
				* to remember and pass back through the debug callback.
				*/
				if (deviceFlags & NVN_DEVICE_FLAG_DEBUG_ENABLE_BIT)
				{
					nvnDeviceInstallDebugCallback(
						&m_Device,
						reinterpret_cast<PFNNVNDEBUGCALLBACKPROC>(&DebugLayerCallback),
						NULL, // For testing purposes; any pointer is OK here.
						NVN_TRUE // NVN_TRUE = Enable the callback.
					);
					BX_TRACE("Installed DebugCallback hook");
				}

				//////////////////////////////////////////////////////////////////////////
				// Queue - TODO: Move this into a queue class?

				NVNqueueBuilder queueBuilder;
				nvnQueueBuilderSetDevice(&queueBuilder, &m_Device);
				nvnQueueBuilderSetDefaults(&queueBuilder);
				nvnQueueBuilderSetComputeMemorySize(&queueBuilder, 0);

				int minQueueCommandMemorySize = 0;
				nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_MIN_SIZE, &minQueueCommandMemorySize);
				nvnQueueBuilderSetCommandMemorySize(&queueBuilder, minQueueCommandMemorySize);
				nvnQueueBuilderSetCommandFlushThreshold(&queueBuilder, minQueueCommandMemorySize);

				size_t neededQueueMemorySize = nvnQueueBuilderGetQueueMemorySize(&queueBuilder);

				if ((neededQueueMemorySize % NVN_MEMORY_POOL_STORAGE_GRANULARITY) != 0)
				{
					BX_CHECK(0, "Memory size reported for queue is not the proper granularity");
				}

				//TODO: Update this to be the "proper" NVN allocator
				bx::CrtAllocator allocator;

				m_pQueueMemory = bx::alignedAlloc(
					&allocator,
					neededQueueMemorySize,
					NVN_MEMORY_POOL_STORAGE_ALIGNMENT);

				nvnQueueBuilderSetQueueMemory(&queueBuilder, m_pQueueMemory, neededQueueMemorySize);

				if (nvnQueueInitialize(&m_Queue, &queueBuilder) == false)
				{
					BX_CHECK(0, "nvnQueueInitialize failed");
				}

				BX_TRACE("Initialised NVN Queue");
				BX_TRACE("\tTotal memory %d KB", neededQueueMemorySize / 1024);
				BX_TRACE("\tCommand Flush threshold: %d KB", minQueueCommandMemorySize / 1024);

				//////////////////////////////////////////////////////////////////////////
				// Command buffer - TODO: Move this into a command buffer class?

				if (!nvnCommandBufferInitialize(&m_CommandBuffer, &m_Device))
				{
					BX_CHECK(0, "nvnCommandBufferInitialize");
				}

				/*
				* Queries the device for the proper control and command
				* memory alignment for a command buffer.
				*/
				int commandBufferCommandAlignment = 0;
				int commandBufferControlAlignment = 0;
				nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_COMMAND_BUFFER_COMMAND_ALIGNMENT, &commandBufferCommandAlignment);
				nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_COMMAND_BUFFER_CONTROL_ALIGNMENT, &commandBufferControlAlignment);

				/* Setup the command buffer memory pool. */
				m_pCommandMemoryPool = new MemoryPool();
				m_pCommandMemoryPool->Init(
					&allocator,
					MemoryPool::Align(g_CommandMemorySize, commandBufferCommandAlignment) * 2,
					NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT,
					&m_Device);

				m_pControlPool = BX_ALIGNED_ALLOC(
					&allocator,
					g_ControlMemorySize,
					commandBufferControlAlignment);

				/* Grab the offset from the memory pool. */
				m_CommandPoolOffset = m_pCommandMemoryPool->GetNewMemoryChunkOffset(
					g_CommandMemorySize,
					commandBufferCommandAlignment);

				/* Provides the command buffer with the command and control memory blocks. */
				nvnCommandBufferAddCommandMemory(
					&m_CommandBuffer,
					m_pCommandMemoryPool->GetMemoryPool(),
					m_CommandPoolOffset,
					g_CommandMemorySize);

				nvnCommandBufferAddControlMemory(
					&m_CommandBuffer,
					m_pControlPool,
					g_ControlMemorySize);

				BX_TRACE("Initialized command buffer");
				BX_TRACE("\tCommand Memory Pool: %dKB", m_pCommandMemoryPool->GetSize() / 1024);
				BX_TRACE("\tCoommand Buffer: %d bytes", g_CommandMemorySize);
				BX_TRACE("\tControl Buffer: %d bytes", g_ControlMemorySize);

				/* Render Target Setting Command Buffer */
				if (!nvnCommandBufferInitialize(&m_RenderTargetCommandBuffer, &m_Device))
				{
					BX_CHECK(0, "nvnCommandBufferInitialize");
				}

				/* Setup the control memory with the proper alignment. */
				m_pRenderTargetControlPool = BX_ALIGNED_ALLOC(
					&allocator, 
					g_ControlMemorySize, 
					commandBufferControlAlignment);

				/* Grab the offset from the memory pool. */
				m_RenderTargetCommandPoolOffset = m_pCommandMemoryPool->GetNewMemoryChunkOffset(g_CommandMemorySize, commandBufferCommandAlignment);

				nvnCommandBufferAddCommandMemory(&m_RenderTargetCommandBuffer, m_pCommandMemoryPool->GetMemoryPool(), m_RenderTargetCommandPoolOffset, g_CommandMemorySize);
				nvnCommandBufferAddControlMemory(&m_RenderTargetCommandBuffer, m_pRenderTargetControlPool, g_ControlMemorySize);

				//////////////////////////////////////////////////////////////////////////
				// On with the show!

				if (!nvnSyncInitialize(&m_CommandBufferSync, &m_Device))
				{
					BX_CHECK(0, "nvnSyncInitialize");
				}

				/*! Initialize the window sync. */
				if (!nvnSyncInitialize(&m_WindowSync, &m_Device))
				{
					BX_CHECK(0, "Failed to initialize window sync");
				}

				m_RenderTargetBuilder;
				nvnTextureBuilderSetDevice(&m_RenderTargetBuilder, &m_Device);
				nvnTextureBuilderSetDefaults(&m_RenderTargetBuilder);

				/* Render targets that need to be displayed to the screen need both the display access and compressible bit. */
				nvnTextureBuilderSetFlags(&m_RenderTargetBuilder, NVN_TEXTURE_FLAGS_DISPLAY_BIT | NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT);
				nvnTextureBuilderSetTarget(&m_RenderTargetBuilder, NVN_TEXTURE_TARGET_2D);
				nvnTextureBuilderSetFormat(&m_RenderTargetBuilder, NVN_FORMAT_RGBA8);
				nvnTextureBuilderSetSize2D(&m_RenderTargetBuilder, 1920, 1080);

				m_ColorTargetSize = nvnTextureBuilderGetStorageSize(&m_RenderTargetBuilder);

				m_pRenderTargetMemoryPool = new MemoryPool();
				m_pRenderTargetMemoryPool->Init(
					&allocator,
					m_ColorTargetSize * g_NumColorBuffers,
					NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS_BIT 
					| NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT 
					| NVN_MEMORY_POOL_FLAGS_COMPRESSIBLE_BIT,
					&m_Device);

				BX_TRACE("Created render targets for screen display");
				BX_TRACE("\tColor target size: %dKB", m_ColorTargetSize / 1024)


				nvnWindowBuilderSetDefaults(&m_WindowBuilder);
				nvnWindowBuilderSetDevice(&m_WindowBuilder, &m_Device);
				nvnWindowBuilderSetNativeWindow(&m_WindowBuilder, nativeWindow);

				BX_TRACE("Created window");

				return true;
			}

			NVNdevice         m_Device;
			NVNsync           m_WindowSync;
			Resolution		  m_Resolution;
			NVNwindow*		  m_pWindow;
			int               m_CurrentWindowIndex;
			size_t            m_ColorTargetSize;
			NVNwindowBuilder  m_WindowBuilder;
			
			NVNtextureBuilder m_RenderTargetBuilder;
			NVNtexture*       m_RenderTargets[g_NumColorBuffers];

			// TODO: These could live inside a queue class
			NVNqueue          m_Queue;
			void*             m_pQueueMemory;

			// TODO: These could live inside a command buffer class?
			MemoryPool*       m_pCommandMemoryPool;

			ptrdiff_t         m_CommandPoolOffset;
			void*             m_pControlPool;
			NVNcommandBuffer  m_CommandBuffer;
			NVNcommandHandle  m_CommandHandle;
			NVNsync           m_CommandBufferSync;

			ptrdiff_t         m_RenderTargetCommandPoolOffset;
			void*             m_pRenderTargetControlPool;
			NVNcommandBuffer  m_RenderTargetCommandBuffer;
			NVNcommandHandle  m_RenderTargetCommandHandle;

			//////////////////////////////////////////////////////////////////////////
			MemoryPool*       m_pRenderTargetMemoryPool;
		};

		static RendererContextNVN* s_renderNVN;

		RendererContextI* rendererCreate()
		{
			s_renderNVN = BX_NEW(g_allocator, RendererContextNVN);
			if (!s_renderNVN->init())
			{
				delete s_renderNVN;
				s_renderNVN = nullptr;
			}
			return s_renderNVN;
		}

		void rendererDestroy()
		{
			BX_DELETE(g_allocator, s_renderNVN);
			s_renderNVN = NULL;
		}
	} /* namespace noop */
} // namespace bgfx
#else

namespace bgfx
{
	namespace nvn
	{
		RendererContextI* rendererCreate()
		{
			return NULL;
		}



		void rendererDestroy()
		{
		}
	} /* namespace nvn */
} // namespace bgfx

#endif
