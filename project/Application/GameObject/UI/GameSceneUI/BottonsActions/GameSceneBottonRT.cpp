#include "GameSceneBottonRT.h"


using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameSceneUIBottonRT::Active(BaseBottonUI& ui)
{

	uint32_t texHandle = TextureManager::LoadPngTexture("normalMap.png");
	ui.SetTexHandle(texHandle);
}

void GameSceneUIBottonRT::Inactive(BaseBottonUI& ui)
{
	uint32_t texHandle = TextureManager::LoadPngTexture("GameUI/GameBottonUIRT.png");
	ui.SetTexHandle(texHandle);
}
