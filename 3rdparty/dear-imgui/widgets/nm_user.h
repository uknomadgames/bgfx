namespace ImGui
{
	struct WindowTypes
	{
		enum eType
		{
			CONSOLE = 0,
			CHOICES = 1,
			TRACE,
			REPLAY,
			//			CHARACTERS,
			STACK,
			PERF,
			SFX,
			DICE,
			FPS,
			PARTICLES,
			CALLSTACK_TREE,
			FILE_EXPLORER,
			ENT_DEBUG,
			ANALYTICS,
			BUMP_PARAMS,
			LAYERS,
			VAR_VIEWER,
			TWEAKER,
			LOBBY,
			NETWORKSOAK,
			CONNECT,
			NUMTYPES,
			ALL = 0x7FFFFFFF,
		};

		static const char *m_pNames[];
	};

	extern int m_windowTypes;

	void EnableWindow(WindowTypes::eType eWin);
	void DisableWindow(WindowTypes::eType eWin);
	void ToggleWindow(WindowTypes::eType eWin);
	bool IsEnabled(WindowTypes::eType eWin);
	bool AnyWindowFocused();
	bool AnyWindowEnabled();
	void SetDPI(int dpi);

	bool MouseOverNextTreeNode(const char *str_id);

	bool AddButton(const char *pText, int *pbEnabled);
	void AddButton(ImGui::WindowTypes::eType type);

	int HoveredWindow();
	ImVec2 GetCurrentWindowDCPos();
	ImVec2 GetWindowMinSize();
	void DontShowImGuiBorders();
	bool IsImGuiEnteringText();
	void GetLastItemRect(ImVec2 &vMin, ImVec2 &vMax);
	//NVGcontext *GetNVG();

	extern bool m_bNewFrameStarted;
	extern bool m_bRemoteEnabled;
	extern bool m_bRemoteRenderOnly;

	void RenderDebugText(ImVec2 pos, const char* text, const char* text_end);
	ImGuiStorage *GetCurrentWindowStorage();
	void SaveSettings();
	ImGuiIO &GetIMGuiIO();
};

extern void RegisterImGuiInputs();
extern void UnregisterImGuiInputs();
extern void UnregisterGameKeyboard();
extern void RegisterGameKeyboard();


//#include "imgui_dock.h"
