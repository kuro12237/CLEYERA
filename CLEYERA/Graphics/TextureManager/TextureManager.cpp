#include "TextureManager.h"

using namespace Math::Vector;

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

void TextureManager::Initialize()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);

	UnUsedFilePath();
	TextureManager::GetInstance()->normalDfTex_ = LoadPngTexture("Resources/Default/normalMap.png");
}

void TextureManager::Finalize()
{
	CoUninitialize();
	//コンテナの中のResourceをすべて削除
	AllUnLoadTexture();
}


uint32_t TextureManager::LoadPngTexture(const string& filePath)
{
	string FilePath = "Resources/textures/" + filePath;
	if (TextureManager::GetInstance()->isCreateObjectLoad_)
	{
		FilePath = filePath;
		TextureManager::GetInstance()->isCreateObjectLoad_ = false;
	}

	//texのファイルの名前が被った場合は入らない
	if (CheckTexDatas(FilePath))
	{
		//新しく作る
		TexData texData = {};
		//DescripterIndexを加算しずらす
		DescriptorManager::IndexIncrement(FilePath);
		//DescripterのIndexを取得
		uint32_t index = DescriptorManager::GetIndex();
		//ハンドル登録
     	texData.index = index;
		//MipImageを作る
		DirectX::ScratchImage mipImages = CreateMipImage(FilePath);
		const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
		texData.resource = CreatepngTexResource(metadata);
		//MipImageを登録
		UploadMipImage(metadata,mipImages, texData);
		//src設定
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc = SrcDescSetting(metadata);
		//Descripterをずらす
		AddDescripter(index, srvDesc, texData.resource.Get());

		//texのサイズ取得
		texData.size.x = static_cast<float>(metadata.width);
		texData.size.y = static_cast<float>(metadata.height);

		//コンテナに保存
		TextureManager::GetInstance()->texDatas_[FilePath] =
			make_unique<TexDataResource>(FilePath, texData);
	}
	return TextureManager::GetInstance()->texDatas_[FilePath]->GetTexHandle();
}

uint32_t TextureManager::LoadDDSTexture(const string& filePath)
{
	string FilePath = "Resources/textures/" + filePath;
	if (TextureManager::GetInstance()->isCreateObjectLoad_)
	{
		FilePath = filePath;
		TextureManager::GetInstance()->isCreateObjectLoad_ = false;
	}

	//texのファイルの名前が被った場合は入らない
	if (CheckTexDatas(FilePath))
	{
		//新しく作る
		TexData texData = {};
		//DescripterIndexを加算しずらす
		DescriptorManager::IndexIncrement(FilePath);
		//DescripterのIndexを取得
		uint32_t index = DescriptorManager::GetIndex();
		//ハンドル登録
		texData.index = index;
		//MipImageを作る
		DirectX::ScratchImage mipImages = CreateDDSMipImage(FilePath);
		const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
		texData.resource = CreatepngTexResource(metadata);
		//MipImageを登録
		UploadMipImage(metadata, mipImages, texData);
		//src設定
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = metadata.format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MostDetailedMip = 0;
		srvDesc.TextureCube.MipLevels = UINT_MAX;
		srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;

		//Descripterをずらす
		AddDescripter(index, srvDesc, texData.resource.Get());

		//texのサイズ取得
		texData.size.x = static_cast<float>(metadata.width);
		texData.size.y = static_cast<float>(metadata.height);

		//コンテナに保存
		TextureManager::GetInstance()->texDatas_[FilePath] =
			make_unique<TexDataResource>(FilePath, texData);
	}
	return TextureManager::GetInstance()->texDatas_[FilePath]->GetTexHandle();
}

void TextureManager::UnLoadTexture(const string& filePath)
{
	TextureManager::GetInstance()->texDatas_[filePath]->texRelease();
	TextureManager::GetInstance()->texDatas_.erase(filePath);
}

void TextureManager::AllUnLoadTexture()
{
	TextureManager::GetInstance()->texDatas_.clear();
}

Math::Vector::Vector2 TextureManager::GetTextureSize(uint32_t texHandle)
{
	Vector2 result{};

	for (const auto& [key, s] : TextureManager::GetInstance()->texDatas_)
	{
		key;
		if (s.get()->GetTexHandle() == texHandle)
		{
			result = s.get()->GetSize();
			break;
		}
	}
	return result;
}


bool TextureManager::CheckTexDatas(string filePath)
{
	if (TextureManager::GetInstance()->texDatas_.find(filePath) == TextureManager::GetInstance()->texDatas_.end())
	{
		return true;
	}
	return false;
}

DirectX::ScratchImage TextureManager::CreateMipImage(const std::string& filePath)
{
	//テクスチャファイルを読み込みプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = LogManager::ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));
	//ミップマップの作成
	DirectX::ScratchImage mipImage{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);
	return mipImage;
}

DirectX::ScratchImage TextureManager::CreateDDSMipImage(const std::string& filePath)
{
	//テクスチャファイルを読み込みプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = LogManager::ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromDDSFile(filePathW.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
	assert(SUCCEEDED(hr));
	//ミップマップの作成

	DirectX::ScratchImage mipImage;

	if (DirectX::IsCompressed(image.GetMetadata().format))
	{
		mipImage =std::move(image);
	}
	else
	{
		assert(0);
	}

	return mipImage;
}

D3D12_RESOURCE_DESC TextureManager::SettingResource(const DirectX::TexMetadata& metadata)
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

D3D12_HEAP_PROPERTIES TextureManager::SettingHeap()
{
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	return heapProperties;
}

void TextureManager::UploadMipImage(const DirectX::TexMetadata& metadata, DirectX::ScratchImage &mipImages,TexData texData)
{
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel)
	{
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
		texData.resource->
			WriteToSubresource(
				UINT(mipLevel),
				nullptr,
				img->pixels,
				UINT(img->rowPitch),
				UINT(img->slicePitch)
			);
	}
}

D3D12_SHADER_RESOURCE_VIEW_DESC TextureManager::SrcDescSetting(const DirectX::TexMetadata& metadata)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC resultSrvDesc{};
	resultSrvDesc.Format = metadata.format;
	resultSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	resultSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	resultSrvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
	return resultSrvDesc;
}




void TextureManager::AddDescripter(uint32_t index, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ID3D12Resource *resource)
{
	//Despcripter
	DescriptorManager::SetCPUDescripterHandle(
		DescriptorManager::GetCPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap(),
		    index),
		index
	);

	DescriptorManager::SetGPUDescripterHandle(
		DescriptorManager::GetGPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap(),
			index),
		index
	);

	DescriptorManager::CGHandlePtr();
	DescriptorManager::CreateShaderResourceView(
		resource,
		srvDesc,
		index);
}

ComPtr<ID3D12Resource> TextureManager::CreatepngTexResource(const DirectX::TexMetadata& metadata)
{
	ComPtr<ID3D12Resource> Resource;
	D3D12_RESOURCE_DESC resourceDesc{};
	D3D12_HEAP_PROPERTIES heapProperties{};
	//リソースの設定
	resourceDesc = SettingResource(metadata);
	heapProperties = SettingHeap();
	//本体を作る
	DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Resource));
	return Resource;
}
struct CD3DX12_HEAP_PROPERTIES : public D3D12_HEAP_PROPERTIES
{
	CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE type, UINT creationNodeMask = 1, UINT nodeMask = 1)
	{
		Type = type;
		CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		CreationNodeMask = creationNodeMask;
		VisibleNodeMask = nodeMask;
	}

	explicit CD3DX12_HEAP_PROPERTIES(const D3D12_HEAP_PROPERTIES& o) :
		D3D12_HEAP_PROPERTIES(o)
	{}
};

