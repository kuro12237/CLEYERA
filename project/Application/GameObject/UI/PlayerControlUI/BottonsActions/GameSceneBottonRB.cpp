#include "GameSceneBottonRB.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameSceneUIBottonRB::Active(BaseBottonUI& ui)
{
	uint32_t texHandle = TextureManager::LoadPngTexture("GameUI/GameBottonUIRB_Active.png");
	ui.SetTexHandle(texHandle);
}

void GameSceneUIBottonRB::Inactive(BaseBottonUI& ui)
{

	uint32_t texHandle = TextureManager::LoadPngTexture("GameUI/GameBottonUIRB.png");
	ui.SetTexHandle(texHandle);
}

bool GameSceneUIBottonRB::ControlRB()
{
	if (Input::PushBotton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		return true;
	}
	return false;
}
