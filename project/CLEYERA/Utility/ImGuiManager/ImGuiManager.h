#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"ImGuiJapaneseGlyphArray.h"

/// <summary>
/// ImGui���g�����߂̐ݒ�֐�
/// </summary>
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
