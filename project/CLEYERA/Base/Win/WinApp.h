#pragma once
#include"Pch.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Engine::Base::Win {

	/// <summary>
	/// ウィンドウズ本体
	/// </summary>
	class WinApp
	{
	public:

		static WinApp* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// winMsgを入手
		/// </summary>
		/// <returns></returns>
		bool WinMsg();
		
		/// <summary>
		/// 終わり
		/// </summary>
		void Finalize();

		/// <summary>
		/// ImGui更新
		/// </summary>
		void ImGuiUpdate();

#pragma region Set
		void SetTiTleName(LPCWSTR  name) { SetWindowText(WinApp::GetInstance()->hwnd_, name); }
#pragma endregion

#pragma region get
		static HWND GetHwnd() { return WinApp::GetInstance()->hwnd_; }
		static WNDCLASS GetWc() { return WinApp::GetInstance()->wc_; }

		static int32_t GetkCilientWidth() { return WinApp::GetInstance()->kWindowWidth; }
		static int32_t GetkCilientHeight() { return WinApp::GetInstance()->kWindowHeight; }
#pragma endregion

	private:

		/// <summary>
		/// ウインドウ作製
		/// </summary>
		static HWND CreateWIND(const int32_t kWidth, const int32_t kHeight, LPCTSTR title, WNDCLASS wc);

		/// <summary>
		/// Proc関数
		/// </summary>
		/// <param name="hwnd"></param>
		/// <param name="msg"></param>
		/// <param name="wparam"></param>
		/// <param name="lparam"></param>
		/// <returns></returns>
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static const int32_t kWindowWidth = 1280;
		static const int32_t kWindowHeight = 720;

		MSG msg{};
		WNDCLASS wc_{};
		HWND hwnd_ = {};
		HWND DebugHwnd_{};

		WinApp() = default;
		~WinApp() = default;
		WinApp(const WinApp&) = delete;
		const WinApp& operator=(const WinApp&) = delete;
	};

}

