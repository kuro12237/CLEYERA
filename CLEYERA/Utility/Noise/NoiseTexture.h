#pragma once
#include"Graphics/TextureManager/TextureManager.h"

class NoiseTexture
{
public:

	static NoiseTexture* GetInstance();

	void Initialize();

	void RootParamerter();

private:

	string name = "Resource/Default/noise.png"; 
	uint32_t index_ = 0;

	NoiseTexture() = default;
	~NoiseTexture() = default;
	NoiseTexture(const NoiseTexture&) = delete;
	const NoiseTexture& operator=(const 	NoiseTexture&) = delete;
};