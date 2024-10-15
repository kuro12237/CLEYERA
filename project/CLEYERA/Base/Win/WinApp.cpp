#include "WinApp.h"
#include<wchar.h>

using namespace Engine::Base::Win;

WinApp *WinApp::GetInstance()
{
	static WinApp instance;
	return &instance;
}


void WinApp::Initialize()
{
	wc_.lpfnWndProc = WinApp::WindowProc;
	wc_.lpszClassName = L"CLEYERA";
	wc_.hInstance = GetModuleHandle(nullptr);
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClass(&wc_);

	RECT wrc = { 0,0,
	WinApp::GetInstance()->kWindowWidth,
	WinApp::GetInstance()->kWindowHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	
	hwnd_=CreateWindow(
		wc_.lpszClassName,
		L"CLEYERA",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wc_.hInstance,
		nullptr
	);
	HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	SendMessage(hwnd_, WM_SETFONT, (WPARAM)hFont, TRUE);

	// ウィンドウタイトルの変更
	ShowWindow(hwnd_, SW_SHOW);

	timeBeginPeriod(1);
}

bool WinApp::WinMsg()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message != WM_QUIT) {
		return true;
	}

	return false;
}

void WinApp::Finalize()
{
	CloseWindow(hwnd_);
}

void WinApp::ImGuiUpdate()
{
	if (ImGui::TreeNode("Windows"))
	{
		ImGui::Text("width : %d height : %d", WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());
		ImGui::TreePop();
	}
}

HWND WinApp::CreateWIND(const int32_t kWidth, const int32_t kHeight, LPCTSTR title, WNDCLASS wc)
{
	wc.lpfnWndProc = WinApp::WindowProc;
	wc.lpszClassName = title;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClass(&wc);

	RECT wrc = { 0,0,
	kWidth,
	kHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	return CreateWindow(
		wc.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);
}

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}
	switch (msg)
	{
		//ウインドウが破棄
	case WM_DESTROY:
		//OSに対しアプリ終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
