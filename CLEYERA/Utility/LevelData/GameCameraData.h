#pragma once
#include"CameraData.h"
#include"Transform/STransformEular.h"
#include"WorldTransform.h"

class GameCameraData
{
public:

	GameCameraData() {};
	~GameCameraData() {};

	void Create(TransformEular t);

	void Update();

#pragma region Get

	const CameraData &GetCamera()  { return camera_; }

#pragma endregion

private:
	string type_;
	CameraData camera_;
	WorldTransform worldTransform_;
	bool isParent_ = false;
};
