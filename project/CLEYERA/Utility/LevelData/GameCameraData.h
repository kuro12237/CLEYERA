#pragma once
#include"CameraData.h"
#include"Transform/STransformEular.h"
#include"WorldTransform.h"
#include"IGameObjectData.h"

class GameCameraData :public IGameObjectData
{
public:

	GameCameraData() {};
	~GameCameraData() {};

	void Create(TransformEular t);


	void WtUpdate(TransformEular transform);

	void Update();

#pragma region Get

	const CameraData &GetCamera()  { return camera_; }

#pragma endregion

private:
	string type_;
	CameraData camera_;
	bool isParent_ = false;
};
