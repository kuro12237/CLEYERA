#pragma once
#include"CameraData.h"
#include"WorldTransform.h"
#include"Input.h"

class PlayerCamera
{
public:
	PlayerCamera() {};
	~PlayerCamera() {};


	void Initialize();

	void Update();

#pragma region Set
	void SetParent(const WorldTransform& w) { worldTransform_ = &w; }
#pragma endregion
#pragma region get

	CameraData GetData() { return cameraData_; }



#pragma endregion

private:

	void RotateMove();

	const WorldTransform* worldTransform_ = nullptr;

	CameraData cameraData_ = {};


	Vector2 distinationAngleXY = {};
};