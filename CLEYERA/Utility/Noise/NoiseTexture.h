#pragma once
#include"Graphics/TextureManager/TextureManager.h"

class NoiseTexture
{
public:

	static NoiseTexture* GetInstance();

	void Initialize();

	void RootParamerter();
	uint32_t GetIndex() { return index_; }

private:

	string name = "Resources/Default/noise.png";
	uint32_t index_ = 0;

	NoiseTexture() = default;
	~NoiseTexture() = default;
	NoiseTexture(const NoiseTexture&) = delete;
	const NoiseTexture& operator=(const 	NoiseTexture&) = delete;
};