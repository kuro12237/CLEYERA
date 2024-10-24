#pragma once
#include"CameraData.h"
#include"WorldTransform.h"
#include"Input.h"

namespace Engine::DebugTools
{
	/// <summary>
	/// デバッグカメラ
	/// </summary>
	class DebugCamera
	{
	public:
		DebugCamera() {};
		~DebugCamera() {};

		void Initialize();

		void ImGuiUpdate();

		void Update();

		/// <summary>
		/// updateの最後
		/// </summary>
		/// <param name="camera"></param>
		/// <returns></returns>
		Engine::Camera::CameraData GetData(const Engine::Camera::CameraData& camera);

	private:

		void RotateMove();

		bool isUse_ = false;
		bool preIsUse = false;

		Engine::Transform::WorldTransform worldTransform_{};
		Engine::Camera::CameraData cameraData_ = {};
		Engine::Camera::CameraData saveCameraData_ = {};


		Math::Vector::Vector3 moveSpeed_ = { 0.25f,0.25f,0.25f };
		Math::Vector::Vector3 rotateSpeed_ = { 0.04f,0.04f,0.04f };
		Math::Vector::Vector3 prerotateSpeed_ = {};

		Math::Vector::Vector3 offset_ = { 0.0f,2.0f,-16.0f };
		Math::Vector::Vector3 DfOffset_ = { 0.0f,2.0f,-16.0f };

		Math::Matrix::Matrix4x4 matRot_ = {};

		bool leftMoveFlag_ = false;

	};
}