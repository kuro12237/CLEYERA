#include "LightingManager.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;
using namespace Engine::Manager;

LightingManager* LightingManager::GetInstance()
{
	static LightingManager instance;
	return &instance;
}

void LightingManager::Initialize()
{
	//Buffer生成
	lightCountBuf_ = make_unique<BufferResource<uint32_t>>();
	lightCountBuf_->CreateResource(1);
	lightCountBuf_->Map();
	lightCountBuf_->Setbuffer(NowTotalLightData_);
	lightCountBuf_->UnMap();

	lightParamsBuf_ = make_unique<BufferResource<PointLight_param>>();
	lightParamsBuf_->CreateResource(NumLight_);
	lightParamsBuf_->CreateInstancingResource(NumLight_, "Light", UINT(sizeof(PointLight_param)));

}

void LightingManager::AddList(PointLight_param& instance)
{
	LightingManager::GetInstance()->LightDatas_.push_back(instance);
	LightingManager::GetInstance()->NowTotalLightData_++;
}


list<PointLight_param> LightingManager::GetLightData()
{
	list<PointLight_param>result = LightingManager::GetInstance()->LightDatas_;
	LightingManager::GetInstance()->LightDatas_.clear();
	return result;
}

void LightingManager::TransfarBuffers()
{
	TransfarBuffer();
	TransfarStructureBuffer();
}

void LightingManager::CallCommand()
{
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	DescriptorManager::rootParamerterCommand(4, lightParamsBuf_->GetSrvIndex());
	lightCountBuf_->CommandCall(5);
}

void LightingManager::TransfarBuffer()
{
	lightCountBuf_->Map();
	lightCountBuf_->Setbuffer(NowTotalLightData_);
	lightCountBuf_->UnMap();
}

void LightingManager::TransfarStructureBuffer()
{
	vector<PointLight_param> param;

	lightParamsBuf_->Map();

	for (auto& light : LightDatas_)
	{
		param.push_back(light);
	}
	lightParamsBuf_->Setbuffer(param,uint32_t(LightDatas_.size()));
	lightParamsBuf_->UnMap();
}
