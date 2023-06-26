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

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// テクスチャのロード
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	DirectX::ScratchImage Load(const std::string &filePath);

	/// <summary>
	/// 
	/// </summary>
	void EndFlame();

private:

};

