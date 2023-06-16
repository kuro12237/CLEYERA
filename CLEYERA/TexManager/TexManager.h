#pragma once
#include <combaseapi.h>
#include"../externals/DirectXTex/DirectXTex/DirectXTex.h"

#include<string>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")
#include<windows.h>
#include<cassert>

#include<dxgidebug.h>
#pragma comment(lib,"dxguid.lib")
#include"../externals/DirectXTex/DirectXTex/d3dx12.h"

#include"../Log/Log.h"
class TexManager
{
public:
	TexManager();
	~TexManager();

	void Initialize();

	DirectX::ScratchImage Load(const std::string &filePath);

	ID3D12Resource* CreateTexResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

	void uploadTexData(ID3D12Resource* tex, const DirectX::ScratchImage& mipImages);


#pragma region  TexResourceの生成
	static D3D12_RESOURCE_DESC  MetadataResourceSetting(const DirectX::TexMetadata& metadata);
	static D3D12_HEAP_PROPERTIES heapProperties();
#pragma endregion

	void EndFlame();

private:

};

