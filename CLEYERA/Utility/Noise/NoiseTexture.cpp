#include "NoiseTexture.h"

NoiseTexture* NoiseTexture::GetInstance()
{
	static NoiseTexture instance;
	return &instance;
}

void NoiseTexture::Initialize()
{
	TextureManager::UnUsedFilePath();
	index_ = TextureManager::LoadPngTexture(name);
}

void NoiseTexture::RootParamerter()
{

}
