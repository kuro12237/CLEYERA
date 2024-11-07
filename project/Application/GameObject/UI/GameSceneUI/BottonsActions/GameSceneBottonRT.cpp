#include "GameSceneBottonRT.h"

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
