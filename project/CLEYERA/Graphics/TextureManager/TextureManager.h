#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"CreateResource.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Graphics/TextureManager/TexDataResource.h"
#include<DirectXTex/DirectXTex.h>
#include"CreateResource/BufferResources.h"


namespace Engine::Manager
{


	/// <summary>
	/// テクスチャを読み込み管理
	/// </summary>
	class TextureManager
	{
	public:

		static TextureManager* GetInstance();

		static void Initialize();
		static void Finalize();

		/// <summary>
		/// pngを読み込み
		/// </summary>
		static uint32_t LoadPngTexture(const string& filePath);

		/// <summary>
		/// DDSを読み込み
		/// </summary>
		static uint32_t LoadDDSTexture(const string& filePath);

		/// <summary>
		/// アンカーポイント計算
		/// </summary>
		static Math::Vector::Vector2 CalcAnkerPos(Math::Vector::Vector2 texSize, Math::Vector::Vector2 ankerPos = { 0.5f,0.5f });

		/// <summary>
		/// ファイルを消す
		/// </summary>
		/// <param name="filePath"></param>
		static void UnLoadTexture(const string& filePath);

		/// <summary>
		/// すべてのファイルを消す
		/// </summary>
		static void AllUnLoadTexture();

		/// <summary>
		/// pngのsizeを取得
		/// </summary>
		static Math::Vector::Vector2 GetTextureSize(uint32_t texHandle);

		static string GetTexFilePath(const uint32_t& texHandle);

		/// <summary>
		/// ファイルパスを一から書くときに使うやつ
		/// </summary>
		static void UnUsedFilePath() { TextureManager::GetInstance()->isCreateObjectLoad_ = true; }

	private:
		[[nodiscard]]
		static ComPtr<ID3D12Resource> UpLoadTexData(ComPtr<ID3D12Resource>resource, const DirectX::ScratchImage& mipImage);

		/// <summary>
		/// テクスチャのリソース作製
		/// </summary>
		/// <param name="metadata"></param>
		/// <returns></returns>
		static ComPtr<ID3D12Resource> CreatepngTexResource(const DirectX::TexMetadata& metadata);

		/// <summary>
		/// MipImageを作製
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		static DirectX::ScratchImage CreateMipImage(const std::string& filePath);

		/// <summary>
		/// DDSのMipImageを作製
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		static DirectX::ScratchImage CreateDDSMipImage(const std::string& filePath);

		/// <summary>
		/// リソース設定
		/// </summary>
		static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

		/// <summary>
		/// ヒープ設定
		/// </summary>
		static D3D12_HEAP_PROPERTIES SettingHeap();

		/// <summary>
		/// MipImageを登録
		/// </summary>
		static void UploadMipImage(const DirectX::TexMetadata& metadata, DirectX::ScratchImage& mipImages, TexData texData);

		/// <summary>
		/// DESCの設定
		/// </summary>
		/// <param name="metadata"></param>
		/// <returns></returns>
		static D3D12_SHADER_RESOURCE_VIEW_DESC SrcDescSetting(const DirectX::TexMetadata& metadata);

		/// <summary>
		/// デスクリプターに登録
		/// </summary>
		/// <param name="index"></param>
		/// <param name="srvDesc"></param>
		/// <param name="resource"></param>
		static void AddDescripter(uint32_t index, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ID3D12Resource* resource);

		/// <summary>
		/// 読み込んだことがある科をチェック
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		static bool CheckTexDatas(string filePath);

		map<string, unique_ptr<TexDataResource>>texDatas_;

		bool isCreateObjectLoad_ = false;

		uint32_t normalDfTex_ = 0;

#pragma region 
		//Singleton
		TextureManager() = default;
		~TextureManager() = default;
		TextureManager(const TextureManager&) = delete;
		const TextureManager& operator=(const TextureManager&) = delete;
#pragma endregion 
	};
}