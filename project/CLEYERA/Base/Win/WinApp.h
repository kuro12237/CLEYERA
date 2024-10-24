#pragma once
#include"Pch.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Engine::Base::Win {

	/// <summary>
	/// �E�B���h�E�Y�{��
	/// </summary>
	class WinApp
	{
	public:

		static WinApp* GetInstance();

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// winMsg�����
		/// </summary>
		/// <returns></returns>
		bool WinMsg();
		
		/// <summary>
		/// �I���
		/// </summary>
		void Finalize();

		/// <summary>
		/// ImGui�X�V
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
		/// �E�C���h�E�쐻
		/// </summary>
		static HWND CreateWIND(const int32_t kWidth, const int32_t kHeight, LPCTSTR title, WNDCLASS wc);

		/// <summary>
		/// Proc�֐�
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

