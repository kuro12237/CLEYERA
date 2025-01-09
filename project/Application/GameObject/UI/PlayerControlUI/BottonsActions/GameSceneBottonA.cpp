#include "GameSceneBottonA.h"

using namespace Engine::Manager;
using namespace Engine;

bool GameSceneUIBottonA::ControlA()
{
	if (Input::PushBotton(XINPUT_GAMEPAD_A))
	{
		return true;
	}
	return false;
}

void GameSceneUIBottonA::Active(BaseBottonUI& ui)
{

	uint32_t texHandle = TextureManager::LoadPngTexture("GameUI/GameBottonUIA_Active.png");
	ui.SetTexHandle(texHandle);
}

void GameSceneUIBottonA::Inactive(BaseBottonUI& ui)
{
	uint32_t texHandle = TextureManager::LoadPngTexture("GameUI/GameBottonUIA.png");
	ui.SetTexHandle(texHandle);
}
