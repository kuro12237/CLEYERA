#include"DescriptorManager.h"

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;


DescriptorManager* DescriptorManager::GetInstance()
{
	static DescriptorManager instance;
	return &instance;
}

void DescriptorManager::Initialize()
{
	ComPtr<ID3D12Device5> device = DirectXCommon::GetInstance()->GetDevice();
	DescriptorManager::GetInstance()->descripterSize_.SRV = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	DescriptorManager::GetInstance()->descripterSize_.RTV = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	DescriptorManager::GetInstance()->descripterSize_.DSV = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	DescriptorManager::GetInstance()->index = 0;
}

void DescriptorManager::BeginFlame()
{
	if (DescriptorManager::GetInstance()->index >= SRV_DESCRIPTOR_MAX)
	{
		LogManager::Log("DescripterManager index Overflow\n");
		assert(0);
	}

}

void DescriptorManager::ImGuiUpdate()
{
	ImGui::Text("SRVindex::%d", DescriptorManager::GetIndex() + 1);

}

void DescriptorManager::Clear()
{
	DescriptorManager::GetInstance()->index = 0;
}

uint32_t DescriptorManager::CreateSRV(ComPtr<ID3D12Resource>& resource, D3D12_SHADER_RESOURCE_VIEW_DESC SrvDesc)
{
	DescriptorManager::GetInstance()->SrvHandleCPU[DescriptorManager::GetInstance()->index] =
		GetCPUDescriptorHandle(
			DescriptorManager::GetInstance()->index
		);

	DescriptorManager::GetInstance()->SrvHandleGPU[DescriptorManager::GetInstance()->index] =
		GetGPUDescriptorHandle(
			DescriptorManager::GetInstance()->index
		);
	DescriptorManager::GetInstance()->SrvHandleCPU[DescriptorManager::GetInstance()->index].ptr +=
		DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	DescriptorManager::GetInstance()->SrvHandleGPU[DescriptorManager::GetInstance()->index].ptr +=
		DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(
		resource.Get(),
		&SrvDesc,
		DescriptorManager::GetInstance()->SrvHandleCPU[DescriptorManager::GetInstance()->index]
	);

	return DescriptorManager::GetInstance()->index;
}

uint32_t DescriptorManager::CreateUAV(ComPtr<ID3D12Resource>& resource, D3D12_UNORDERED_ACCESS_VIEW_DESC desc)
{

	SrvHandleCPU[index] =
		GetCPUDescriptorHandle(
			index
		);

	SrvHandleGPU[index] =
		GetGPUDescriptorHandle(
			index
		);

	DescriptorManager::GetInstance()->SrvHandleCPU[DescriptorManager::GetInstance()->index].ptr +=
		DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	DescriptorManager::GetInstance()->SrvHandleGPU[DescriptorManager::GetInstance()->index].ptr +=
		DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	DirectXCommon::GetInstance()->GetDevice()->CreateUnorderedAccessView(
		resource.Get(),
		nullptr,
		&desc,
		SrvHandleCPU[index]
	);

	return DescriptorManager::GetInstance()->index;
}

void DescriptorManager::rootParamerterCommand(UINT rootPatramerterIndex, uint32_t texhandle)
{
	Commands command = DirectXCommon::GetInstance()->GetCommands();
	ID3D12DescriptorHeap* heap[] = { DirectXCommon::GetInstance()->GetSrvHeap() };
	command.m_pList->SetDescriptorHeaps(1, heap);

	command.m_pList->SetGraphicsRootDescriptorTable(
		rootPatramerterIndex,
		DescriptorManager::GetInstance()->SrvHandleGPU[texhandle]
	);
}

void DescriptorManager::ComputeRootParamerterCommand(UINT rootParamIndex, uint32_t index)
{
	ID3D12DescriptorHeap* heap[] = { DirectXCommon::GetInstance()->GetSrvHeap() };
	
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = SrvHandleGPU[index];
	Commands command = DirectXCommon::GetInstance()->GetCommands();
	command.m_pList->SetDescriptorHeaps(1, heap);
	command.m_pList->SetComputeRootDescriptorTable(
		rootParamIndex,
		gpuHandle
	);
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorManager::GetCPUDescriptorHandle(uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = DirectXCommon::GetInstance()->GetSrvHeap()->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (DescriptorManager::GetInstance()->descripterSize_.SRV * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorManager::GetGPUDescriptorHandle(uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = DirectXCommon::GetInstance()->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (DescriptorManager::GetInstance()->descripterSize_.SRV * index);
	return handleGPU;
}

void DescriptorManager::CGHandlePtr()
{
	DescriptorManager::GetInstance()->SrvHandleCPU[DescriptorManager::GetInstance()->index].ptr
		+= DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	DescriptorManager::GetInstance()->SrvHandleGPU[DescriptorManager::GetInstance()->index].ptr
		+= DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void DescriptorManager::IndexIncrement(const string& name)
{
	DescriptorManager::GetInstance()->index++;
	DescriptorManager::GetInstance()->descripterDatas_[name] = std::make_unique<DescripterData>(DescriptorManager::GetInstance()->index, name);
}

void DescriptorManager::SetBuffer(const string& name, ComPtr<ID3D12Resource> buf)
{
	DescriptorManager::GetInstance()->descripterDatas_[name]->SetBuf(buf);
}

bool DescriptorManager::CheckData(const string& name)
{
	if (DescriptorManager::GetInstance()->descripterDatas_.find(name) == DescriptorManager::GetInstance()->descripterDatas_.end())
	{
		return true;
	}
	return false;
}

uint32_t DescriptorManager::CheckDatasIndex(const string& name)
{
	return DescriptorManager::GetInstance()->descripterDatas_[name]->GetIndex();
}


void DescriptorManager::CreateShaderResourceView(ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, uint32_t index)
{
	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(
		resource,
		&srvDesc,
		DescriptorManager::GetInstance()->SrvHandleCPU[index]);
}
