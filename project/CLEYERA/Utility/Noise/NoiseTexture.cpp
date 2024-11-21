#include "NoiseTexture.h"


using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

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
