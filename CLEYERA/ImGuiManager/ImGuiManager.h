#pragma once

#include"../Setup/DirectXSetup.h"
#include"../Setup/WinSetup.h"
#include"../externals/imgui/imgui.h"
#include"../externals/imgui/imgui_impl_win32.h"
#include"../externals/imgui/imgui_impl_dx12.h"

class ImGuiManager
{
public:

	ImGuiManager();

	void Initialize(WindowsSetup *WinSetup_,DirectXSetup *DXSetup_);


	void BeginFlame(DirectXSetup *DXSetup_);


	void EndFlame(DirectXSetup *DXSetup_);

	void Release();
private:

};


