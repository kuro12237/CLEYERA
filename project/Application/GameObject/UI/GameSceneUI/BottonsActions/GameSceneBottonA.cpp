#include "GameSceneBottonA.h"

void GameSceneUIBottonA::Active(BaseBottonUI& ui)
{

	uint32_t texHandle = TextureManager::LoadPngTexture("normalMap.png");
	ui.SetTexHandle(texHandle);
}

void GameSceneUIBottonA::Inactive(BaseBottonUI& ui)
{
	uint32_t texHandle = TextureManager::LoadPngTexture("GameUI/GameBottonUIA.png");
	ui.SetTexHandle(texHandle);
}
