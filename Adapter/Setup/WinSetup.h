#pragma once
#include<windows.h>

#include<string>
#include<format>
//#include"Log.h"

class WindowsSetup
{
public:
	WindowsSetup();
	~WindowsSetup();

	/// <summary>
	/// ウインドウの表示・初期化
	/// </summary>
	/// <param name="Width"></param>
	/// <param name="Height"></param>
	void Initialize(const int32_t  kClientWidth, const int32_t  kClientHeight);

	/// <summary>
	///ウインドウメッセージ処理 
	/// </summary>
	/// <param name="msg"></param>
	void WinMSG(MSG& msg);


	/// <summary>
	/// Close
	/// </summary>
	void Deleate();


	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	HWND SetHwnd()
	{
		return hwnd;
	}

private:

	//ウインドウクラス
	WNDCLASS wc_{};

	HWND hwnd;
};