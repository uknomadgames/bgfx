namespace ImGui
{
	int g_DPI;

	void SetDPI(int dpi)
	{
		//ImGuiState& g = *GImGui;
		//g.IO.FontGlobalScale = (float)dpi / 72.0f;
		//if (g.IO.FontGlobalScale > 2.0f)
		//{
		//	g.IO.FontGlobalScale = 2.0f;
		//}
	}

	const char *WindowTypes::m_pNames[] = {
		"CONSOLE",
		"CHOICES",
		"TRACE",
		"REPLAY",
//		"CHARACTERS",
		"STACK",
		"PERF",
		"AUDIO",
		"DICE",
		"FPS",
		"PARTICLES",
		"CALLSTACK_TREE",
		"FILE_EXPLORER",
		"ENT_DEBUG",
		"ANALYTICS",
		"BUMP",
		"LAYERS",
		"VAR_VIEWER",
		"TWEAKER",
		"LOBBY",
		"NETWORKSOAK",
		"CONNECT"

	};

	static const size_t windowTypeNameCount = sizeof(WindowTypes::m_pNames) / sizeof(WindowTypes::m_pNames[0]);
	static_assert(windowTypeNameCount == WindowTypes::NUMTYPES, "Not all window types given a name");

	bool AnyWindowFocused()
	{
		return false;
		//ImGuiState& g = *GImGui;
		//return g.FocusedWindow != 0;
	};

	bool m_bNewFrameStarted = false;
	bool m_bRemoteEnabled = true;
	bool m_bRemoteRenderOnly = false;

	int m_windowTypes = 0;

	void EnableWindow(WindowTypes::eType eWin)
	{
		m_windowTypes = ((int)m_windowTypes | (int)(1<<eWin));
	}

	void DisableWindow(WindowTypes::eType eWin)
	{
		m_windowTypes = ((int)m_windowTypes & ~(int)(1<<eWin));
		if(!AnyWindowEnabled())
			FocusWindow(NULL);
	}

	void ToggleWindow(WindowTypes::eType eWin)
	{
		m_windowTypes = ((int)m_windowTypes ^ (int)(1<<eWin));
		if(m_windowTypes & (1<<eWin))
			SetWindowFocus(WindowTypes::m_pNames[eWin]);
		if(!AnyWindowEnabled())
			FocusWindow(NULL);
	}

	bool IsEnabled(WindowTypes::eType eWin)
	{
		return (ImGui::m_windowTypes & (1 << eWin)) != 0;
	}

	bool AnyWindowEnabled()
	{
		return m_windowTypes != 0;
	}

	bool MouseOverNextTreeNode(const char *str_id)
	{
//		static const ImVec2 label_size( 150, 22 );
		/*ImGuiContext &g = *GImGui;*/
//		ImGuiWindow *window = ImGui::GetCurrentWindow();
//		const float frame_height = ImMax( ImMin( window->DC.CurrentLineSize.y, g.FontSize ), label_size.y );
//		ImRect bb = ImRect( window->DC.CursorPos, ImVec2( window->Pos.x + ImGui::GetContentRegionMax().x, window->DC.CursorPos.y + frame_height ) );
//		TFF //	return ImGui::IsHovered( bb, window->GetID( str_id ), 0 );

		ImGuiID thisId = ImGui::GetID(str_id);
		if(ImGui::GetHoveredID() == thisId)
			return true;
		return false;
	}

	ImVec4 cGreen = { 0, 0.5f, 0, 1 };
	ImVec4 cRed = { 0.5f, 0, 0, 1 };

	bool AddButton(const char *pText, int *pbEnabled)
	{
		ImVec4	colour = cRed;
		if (pbEnabled && *pbEnabled)
		{
			colour = *pbEnabled ? cGreen : cRed;
		}

		ImGui::PushStyleColor(ImGuiCol_Button, colour);
		bool bRes = ImGui::SmallButton(pText);
		if (bRes)
		{
			if (pbEnabled)
				*pbEnabled = 1 - *pbEnabled;
		}

		ImGui::PopStyleColor();

		return bRes;
	}

	void AddButton(ImGui::WindowTypes::eType type)
	{
		ImGui::SameLine(0, 1);
		ImVec4	colour = ImGui::IsEnabled(type) ? cGreen : cRed;
		ImGui::PushStyleColor(ImGuiCol_Button, colour);
		if (ImGui::SmallButton(ImGui::WindowTypes::m_pNames[type]))
			ImGui::ToggleWindow(type);
		ImGui::PopStyleColor();
	}

	int HoveredWindow()
	{
		return GImGui->HoveredWindow ? 1 : 0;
	}

	ImVec2 GetCurrentWindowDCPos()
	{
		return GImGui->CurrentWindow->DC.CursorPos;
	}

	ImVec2 GetWindowMinSize()
	{
		return GImGui->Style.WindowMinSize;
	}

	void GetLastItemRect(ImVec2 &vMin, ImVec2 &vMax)
	{
		vMax = GImGui->CurrentWindow->DC.LastItemRect.Max;
		vMin = GImGui->CurrentWindow->DC.LastItemRect.Min;
	}


	void DontShowImGuiBorders()
	{
		ImGui::GetCurrentWindow()->Flags = ImGui::GetCurrentWindow()->Flags;
	}

	bool IsImGuiEnteringText()
	{
		return(GImGui->ActiveId && GImGui->ActiveId == GImGui->InputTextState.ID);
	}

	//void AddButtons()
	//{
	//	for (int t = (int)ImGui::WindowTypes::TRACE; t < (int)ImGui::WindowTypes::NUMTYPES; t++)
	//	{
	//		ImGui::SameLine(0, 1);
	//		AddButton((ImGui::WindowTypes::eType)t);
	//	}

	//	AddButton("Tweaker", &g_bShowTweakerUI);
	//	AddButton("Mounted DZ", &g_bShowMounted);
	//}


	void RenderDebugText(ImVec2 pos, const char* text, const char* text_end) {
		RenderText(pos, text, text_end, false);
	}


	ImGuiStorage *GetCurrentWindowStorage()
	{
		return GetCurrentWindow()->DC.StateStorage;
	}

	void SaveSettings()
	{
		SaveIniSettingsToDisk(GImGui->IO.IniFilename);
	}

	ImGuiIO &GetIMGuiIO()
	{
		return GImGui->IO;
	}
};