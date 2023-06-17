#include"TexManager.h"

TexManager::TexManager()
{
}

TexManager::~TexManager()
{
}

void TexManager::SetDevice(ID3D12Device* device_)
{

	device = device_;
}



void TexManager::Initialize()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);

}

DirectX::ScratchImage TexManager::Load(const std::string& filePath)
{
	//テクスチャファイルを読み込みプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));
	//ミップマップの作成
	DirectX::ScratchImage mipImage{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);

	return mipImage;
	mipImage.Release();
}

void TexManager::UploadTexData(ID3D12Resource* tex, const DirectX::ScratchImage& mipImage)
{
	const DirectX::TexMetadata& metadata = mipImage.GetMetadata();

	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel)
	{
		const DirectX::Image* img = mipImage.GetImage(mipLevel, 0, 0);

		HRESULT hr =
			tex->WriteToSubresource(
				UINT(mipLevel),
				nullptr,
				img->pixels,
				UINT(img->rowPitch),
				UINT(img->slicePitch)
			);
		assert(SUCCEEDED(hr));

		
	}
	
}




ID3D12Resource* TexManager::CreateTexResource(const DirectX::TexMetadata& metadata)
{
	ID3D12Resource* Resource;

	D3D12_RESOURCE_DESC resourceDesc{};
	D3D12_HEAP_PROPERTIES heapProperties{};

	//リソースの設定
	resourceDesc = SettingResource(metadata);
	heapProperties = SettingHeap();
    
	//本体を作る
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Resource));
	assert(SUCCEEDED(hr));

	return Resource;
	Resource->Release();
}

D3D12_RESOURCE_DESC TexManager::SettingResource(const DirectX::TexMetadata& metadata)
{
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	resourceDesc.Format = metadata.format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);

	return resourceDesc;
	
}

D3D12_HEAP_PROPERTIES TexManager::SettingHeap()
{
	D3D12_HEAP_PROPERTIES heapProperties{};

	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;


	return heapProperties;
	
}

void TexManager::EndFlame()
{

	CoUninitialize();
}
