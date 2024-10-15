#include "RTVDescripterManager.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;


RTVDescriptorManager* RTVDescriptorManager::GetInstance()
{
	static RTVDescriptorManager instance;
	return &instance;
}

D3D12_CPU_DESCRIPTOR_HANDLE RTVDescriptorManager::GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);
	return handleCPU;
}

void RTVDescriptorManager::Initialize()
{
	ComPtr<ID3D12Device>device = DirectXCommon::GetInstance()->GetDevice();
	RTVDescriptorManager::GetInstance()->pointerSize_ = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void RTVDescriptorManager::BeginFlame()
{
	if (RTVDescriptorManager::GetInstance()->index_>=RTV_DESCRIPTOR_MAX)
	{
		LogManager::Log("RTV Index Overflow\n");
		assert(0);
	}
}

void RTVDescriptorManager::ImGuiUpdate()
{
		ImGui::Text("RTVindex::%d", RTVDescriptorManager::GetIndex()+1);
}

bool RTVDescriptorManager::CheckData(const string& name)
{
	if (RTVDescriptorManager::GetInstance()->datas_.find(name) == RTVDescriptorManager::GetInstance()->datas_.end())
	{
		return true;
	}
	return false;
}

uint32_t RTVDescriptorManager::CheckDatasIndex(const string& name)
{
	return RTVDescriptorManager::GetInstance()->datas_[name]->GetIndex();

}

void RTVDescriptorManager::IndexIncrement(const string &name)
{
	RTVDescriptorManager::GetInstance()->index_++;
	RTVDescriptorManager::GetInstance()->datas_[name] =  std::make_unique<DescripterData>(RTVDescriptorManager::GetInstance()->index_, name);
}

void RTVDescriptorManager::AddPointer(ComPtr<ID3D12Resource> resource, D3D12_RENDER_TARGET_VIEW_DESC desc)
{
	RTVDescriptorManager::GetInstance()->handle_[RTVDescriptorManager::GetInstance()->index_] =
	   RTVDescriptorManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetRtv().m_pDescritorHeap.Get(),
		   DescriptorManager::GetDescripterSize().RTV,
            RTVDescriptorManager::GetInstance()->index_
		);
	DirectXCommon::GetInstance()->GetDevice()->CreateRenderTargetView(resource.Get(), &desc, RTVDescriptorManager::GetInstance()->handle_[RTVDescriptorManager::GetInstance()->index_]);

}
