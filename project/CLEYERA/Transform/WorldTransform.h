#pragma once
#include"Pch.h"
#include"Matrix/MatrixTransform.h"
#include"CreateResource.h"
#include"CameraData.h"
#include"WinApp.h"
#include"BufferResources.h"
#include"Transform/STransformEular.h"
enum Projection
{
	PerspectiveFov = 0,
	OrthographicMatrix = 1
};

namespace Engine::Transform
{
	using namespace Engine::Buffer;

	/// <summary>
	/// ワールドデータ
	/// </summary>
	struct WorldTransform
	{
		~WorldTransform() {};

		TransformEular transform = { {1.0f,1.0f,1.0f},{},{} };
		Math::Qua::Quaternion quaternion = {};

		Math::Matrix::Matrix4x4 matWorld = {};
		const WorldTransform* parent = {};

		shared_ptr<Engine::Buffer::BufferResource<TransformationMatrix>>buffer_ = nullptr;

		/// <summary>
		/// GPUに送る用
		/// </summary>
		TransformationMatrix BufferMatrix_ = {};

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// S,R,Tを設定
		/// </summary>
		/// <param name="s"></param>
		/// <param name="r"></param>
		/// <param name="t"></param>
		void SRTSetting(Math::Vector::Vector3 s = { 1,1,1 }, Math::Vector::Vector3 r = { 0,0,0 }, Math::Vector::Vector3 t = { 0,0,0 });
		
		/// <summary>
		/// 更新
		/// </summary>
		void UpdateMatrix();

		/// <summary>
		/// GOUに転送
		/// </summary>
		void TransfarMatrix();

		
		/// <summary>
		/// 親子付け関数
		/// </summary>
		/// <param name="別のtransform"></param>
		void SetParent(const WorldTransform& w) { parent = &w; }

		/// <summary>
		/// 親子付け解除
		/// </summary>
		void DeleateParent();

#pragma region Get
		Math::Vector::Vector3 GetWorldPosition();
		Math::Vector::Vector3 GetWorldRotate();
		Math::Vector::Vector3 GetWorldScale();

		Math::Matrix::Matrix4x4 GetMat() { return matWorld; }
#pragma endregion
	private:
		/// <summary>
		/// バッファ作成
		/// </summary>
		void CreateBuffer();

		/// <summary>
		/// bufferMap
		/// </summary>
		void Map();

		/// <summary>
		/// bufferUnMap
		/// </summary>
		void UnMap();
	};

}