#include "DSVDescriptorManager.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;

DSVDescriptorManager* DSVDescriptorManager::GetInstance()
{
    static DSVDescriptorManager instance;
    return &instance;
}

void DSVDescriptorManager::Initialize()
{
    ComPtr<ID3D12Device5>device = DirectXCommon::GetInstance()->GetDevice();
    DSVDescriptorManager::GetInstance()->pointerSize_ = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

void DSVDescriptorManager::BeginFlame()
{
    if (DSVDescriptorManager::GetInstance()->index >= DSV_DESCRIPTOR_MAX)
    {
        LogManager::Log("DSV index overflow");
        assert(0);
    }
}

void DSVDescriptorManager::ImGuiUpdate()
{
    ImGui::Text("DSVindex::%d", DSVDescriptorManager::GetInstance()->index+1);
}

void DSVDescriptorManager::IndexIncrement(const string& name)
{
    DSVDescriptorManager::GetInstance()->index++;
    DSVDescriptorManager::GetInstance()->datas_[name] = make_unique<DescripterData>(DSVDescriptorManager::GetInstance()->index, name);
}

void DSVDescriptorManager::AddPointer(ComPtr<ID3D12Resource> resource, D3D12_DEPTH_STENCIL_VIEW_DESC desc)
{
    ComPtr<ID3D12Device5>device = DirectXCommon::GetInstance()->GetDevice();
    DSVDescriptorManager::GetInstance()->pointerSize_ = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    uint32_t index = DSVDescriptorManager::GetInstance()->index;

    DSVDescriptorManager::GetInstance()->handle_[index] =
        DSVDescriptorManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetDsvHeap(),
            DSVDescriptorManager::GetInstance()->pointerSize_,
            index
        );

    device->CreateDepthStencilView(resource.Get(),
        &desc,
        DSVDescriptorManager::GetInstance()->handle_[index]
    );
}

bool DSVDescriptorManager::CheckData(const string& name)
{
    if (DSVDescriptorManager::GetInstance()->datas_.find(name) == DSVDescriptorManager::GetInstance()->datas_.end())
    {
        return true;
    }
    return false;
}

uint32_t DSVDescriptorManager::CheckDatasIndex(const string& name)
{

    return DSVDescriptorManager::GetInstance()->datas_[name]->GetIndex();
}

D3D12_CPU_DESCRIPTOR_HANDLE DSVDescriptorManager::GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{

    D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
    handleCPU.ptr += (descriptorSize * index);
    return handleCPU;
}
