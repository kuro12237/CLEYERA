#include"TexManager.h"

TexManager::TexManager()
{
}

TexManager::~TexManager()
{
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
}

ID3D12Resource* TexManager::CreateTexResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
{
	//リリースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc = MetadataResourceSetting(metadata);

	//利用するheapの設定
	D3D12_HEAP_PROPERTIES heapProperties;

	//実際に生成
	ID3D12Resource* resource = nullptr;
	
	HRESULT hr = device->CreateCommittedResource
	(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_READ,
		nullptr,
		IID_PPV_ARGS(&resource)
	);
	assert(SUCCEEDED(hr));
	
	return resource;
}

void TexManager::uploadTexData(ID3D12Resource* tex, const DirectX::ScratchImage& mipImages)
{
	const DirectX::TexMetadata& metadats = mipImages.GetMetadata();

	for (size_t mipLevel = 0; mipLevel < metadats.mipLevels; ++mipLevel)
	{
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);

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


#pragma region  TexResourceの生成



D3D12_RESOURCE_DESC TexManager::MetadataResourceSetting(const DirectX::TexMetadata& metadata)
{
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.arraySize);
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	resourceDesc.Format = metadata.format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_UNKNOWN(metadata.dimension);
	return resourceDesc;
}

D3D12_HEAP_PROPERTIES TexManager::heapProperties()
{
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	return heapProperties;

}
#pragma endregion



void TexManager::EndFlame()
{

	CoUninitialize();
}
