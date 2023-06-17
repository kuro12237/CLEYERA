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

	void SetDevice(ID3D12Device* device_);

	void Initialize();


	DirectX::ScratchImage Load(const std::string &filePath);

	void UploadTexData(ID3D12Resource* tex, const DirectX::ScratchImage& mipImage);


	ID3D12Resource* CreateTexResource(const DirectX::TexMetadata& metadata);
	
	/// <summary>
	///	リソースの設定 
	/// </summary>
	/// <param name="metadata"></param>
	/// <returns></returns>
	static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);
	
	/// <summary>
	/// ヒープの設定
	/// </summary>
	/// <returns></returns>
	static D3D12_HEAP_PROPERTIES SettingHeap();

	void EndFlame();

private:

	ID3D12Device* device;
};

