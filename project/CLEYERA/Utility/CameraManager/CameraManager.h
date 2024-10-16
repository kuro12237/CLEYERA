#pragma once
#include"Pch.h"
#include"CameraData.h"

namespace Engine::Manager
{
	using namespace Engine::Camera;

	/// <summary>
	/// カメラ管理クラスカメラをこのクラスに設定する
	/// </summary>
	class CameraManager
	{
	public:

		static CameraManager* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

	
		/// <summary>
		/// カメラをセット
		/// </summary>
		/// <param name="camera"></param>
		void ResetCamera(const CameraData& camera);

#pragma region Get
		const CameraData* GetCameraData() { return cameraData_; }
#pragma endregion

		/// <summary>
		/// 使用しない
		/// </summary>
		/// <param name="num"></param>
		void PsCommandCall(const uint32_t& num);

		/// <summary>
		/// 使用しない
		/// </summary>
		/// <param name="num"></param>
		void VsCommandCall(const uint32_t& num);

	private:

		const CameraData* cameraData_ = nullptr;

		CameraManager() = default;
		~CameraManager() = default;
		CameraManager(const CameraManager&) = delete;
		const CameraManager& operator=(const 	CameraManager&) = delete;
	};
}