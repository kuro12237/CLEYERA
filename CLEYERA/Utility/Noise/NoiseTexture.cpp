#include "NoiseTexture.h"

NoiseTexture* NoiseTexture::GetInstance()
{
	static NoiseTexture instance;
	return &instance;
}

void NoiseTexture::Initialize()
{
	index_ = TextureManager::LoadPngTexture(name);
}

void NoiseTexture::RootParamerter()
{

}
