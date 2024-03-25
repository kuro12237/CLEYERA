#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"ImGuiJapaneseGlyphArray.h"

class ImGuiManager
{
public:
	ImGuiManager();
	~ImGuiManager();

	static void Initialize();

	static void BeginFlame();

	static void EndFlame();

	static void Finalize();
private:

};
