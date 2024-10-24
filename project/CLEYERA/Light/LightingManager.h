#pragma once
#include"Light.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#define LIGHT_MAX 50
#include"BufferResources.h"

namespace Engine::Light
{
	//ライトの合計数
	struct LightCount
	{
		int32_t count;
		float padding[2];
	};
}
namespace Engine::Manager {


	using namespace Engine::Buffer;
	using namespace Engine::Light;

	/// <summary>
	/// ライト管理クラス
	/// </summary>
	class LightingManager
	{
	public:

		static LightingManager* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 登録したものを削除
		/// </summary>
		static void ClearList()
		{
			LightingManager::GetInstance()->LightDatas_.clear();
			LightingManager::GetInstance()->NowTotalLightData_ = 0;
		}

		/// <summary>
		/// Listの登録
		/// </summary>
		/// <param name="instance"></param>
		static void AddList(PointLight_param& instance);

#pragma region Get
		static list<PointLight_param> GetLightData();
		static ID3D12Resource* GetBuffer() { return LightingManager::GetInstance()->lightCountBuf_->GetBuffer(); }
		static uint32_t GetNowLight() { return  LightingManager::GetInstance()->NowTotalLightData_; }

#pragma endregion

		/// <summary>
		/// データを転送
		/// </summary>
		void TransfarBuffers();

		/// <summary>
		/// ライトのコマンドを積む
		/// </summary>
		void CallCommand();

	private:

		/// <summary>
		/// Mapする
		/// </summary>
		void TransfarBuffer();

		/// <summary>
		/// structureの物をMap
		/// </summary>
		void TransfarStructureBuffer();

		/// <summary>
		/// Lightの合計の数値を送る用
		/// </summary>

		unique_ptr<BufferResource<uint32_t>>lightCountBuf_;


		/// <summary>
		/// ァ糸のパラメータを送る
		/// </summary>
		unique_ptr<BufferResource<PointLight_param>>lightParamsBuf_;

		const uint32_t NumLight_ = LIGHT_MAX;

		uint32_t NowTotalLightData_ = 0;

		list<PointLight_param>LightDatas_;

	};
}