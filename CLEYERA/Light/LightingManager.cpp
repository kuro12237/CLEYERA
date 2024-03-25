#include "LightingManager.h"

LightingManager* LightingManager::GetInstance()
{
    static LightingManager instance;
    return &instance;
}

void LightingManager::Initialize()
{
    //Buffer生成
    LightingManager::GetInstance()->buffer_ = 
        CreateResources::CreateBufferResource(sizeof(LightCount));
    LightingManager::GetInstance()->structureBuffer_ = 
        CreateResources::CreateBufferResource(sizeof(PointLight_param)* LightingManager::GetInstance()->NumLight_);

    //descripter生成
    LightingManager::GetInstance()->dsvHandle_ = DescriptorManager::CreateInstancingSRV(
        LightingManager::GetInstance()->NumLight_,
        LightingManager::GetInstance()->structureBuffer_,
        sizeof(PointLight_param)
    );
}

void LightingManager::AddList(PointLight_param& instance)
{
    LightingManager::GetInstance()->LightDatas_.push_back(instance);
    LightingManager::GetInstance()->NowTotalLightData_++;
}


list<PointLight_param> LightingManager::GetLightData()
{
    list<PointLight_param>result =LightingManager::GetInstance()->LightDatas_;
    LightingManager::GetInstance()->LightDatas_.clear();
    return result;
}

void LightingManager::TransfarBuffers()
{
    TransfarBuffer();
    TransfarStructureBuffer();
}

void LightingManager::TransfarBuffer()
{
    LightCount* TotalLight;
    LightingManager::GetInstance()->buffer_->Map(0, nullptr, reinterpret_cast<void**>(&TotalLight));
    TotalLight->count = LightingManager::GetInstance()->NowTotalLightData_;
    LightingManager::GetInstance()->buffer_->Unmap(0, nullptr);
}

void LightingManager::TransfarStructureBuffer()
{
    PointLight_param* param;
    LightingManager::GetInstance()->structureBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&param));

    uint32_t count = 0;
    for(PointLight_param p : LightingManager::GetInstance()->LightDatas_)
    {
        param[count] = p; 
        count ++;
    }
   LightingManager::GetInstance()->structureBuffer_->Unmap(0, nullptr);
}
