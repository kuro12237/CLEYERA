#pragma once
#include"Light.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#define LIGHT_MAX 50
#include"BufferResources.h"

struct LightCount
{
	int32_t count;
	float padding[2];
};

class LightingManager
{
public:
	
	static LightingManager* GetInstance();

	void Initialize();

	static void ClearList()
	{
		LightingManager::GetInstance()->LightDatas_.clear();
		LightingManager::GetInstance()->NowTotalLightData_ = 0;
	}
	static void AddList(PointLight_param&instance);

	static list<PointLight_param> GetLightData();

	static ID3D12Resource* GetBuffer() {return LightingManager::GetInstance()->lightCountBuf_->GetBuffer();}

	void TransfarBuffers();

	static uint32_t GetNowLight() {return  LightingManager::GetInstance()->NowTotalLightData_; }

	void CallCommand();

private:

	void TransfarBuffer();

	void TransfarStructureBuffer();

	/// <summary>
	/// Lightの合計の数値を送る用
	/// </summary>
	
	unique_ptr<BufferResource<uint32_t>>lightCountBuf_;


	/// <summary>
	/// ァ糸のパラメータを送る
	/// </summary>
	unique_ptr<BufferResource<PointLight_param>>lightParamsBuf_;

	const uint32_t NumLight_ = LIGHT_MAX;

	uint32_t NowTotalLightData_ = 0;

	list<PointLight_param>LightDatas_;

};