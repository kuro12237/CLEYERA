#pragma once
#include"DirectXCommon.h"

struct  SPostEffectData
{
	std::string name;
	uint32_t rtvIndex;
	uint32_t srvIndex;
	uint32_t dsvindex;
	ComPtr<ID3D12Resource> resource;
	ComPtr<ID3D12Resource> depthBuffer_ = nullptr;

};

class PostEffectData
{
public:
	PostEffectData(SPostEffectData data)
	{
		data_ = data;
	};
	~PostEffectData() {};

	SPostEffectData GetData() { return data_; };

private:

	SPostEffectData data_ = {};
};