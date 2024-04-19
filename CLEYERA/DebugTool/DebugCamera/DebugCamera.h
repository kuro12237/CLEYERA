#pragma once
#include"CameraData.h"
#include"WorldTransform.h"
#include"Input.h"

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
	CameraData GetData(const CameraData& camera);

private:

	void RotateMove();

	void TranslateMove();

	bool isUse_ = false;
	bool preIsUse = false;

	WorldTransform worldTransform_{};
	CameraData cameraData_ = {};
	CameraData saveCameraData_ = {};


	Math::Vector::Vector3 moveSpeed_ = { 0.25f,0.25f,0.25f };
	Math::Vector::Vector3 rotateSpeed_ = { 0.04f,0.04f,0.04f };
	Math::Vector::Vector3 prerotateSpeed_ = {};

	Math::Vector::Vector3 offset_ = { 0.0f,2.0f,-16.0f };
	Math::Vector::Vector3 DfOffset_ = {0.0f,2.0f,-16.0f};

	Math::Matrix::Matrix4x4 matRot_ = {};

	bool leftMoveFlag_ = false;


};
