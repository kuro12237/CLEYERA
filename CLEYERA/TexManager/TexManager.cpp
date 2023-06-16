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




void TexManager::EndFlame()
{

	CoUninitialize();
}
