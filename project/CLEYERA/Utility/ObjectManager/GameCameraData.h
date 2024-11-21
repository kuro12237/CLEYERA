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

	void Create(Engine::Transform::TransformEular t);

	void WtUpdate(Engine::Transform::TransformEular transform);

	void Update();

#pragma region Get

	const Engine::Camera::CameraData &GetCamera()  { return camera_; }
#pragma endregion

private:
	string type_;
	Engine::Camera::CameraData camera_;
	bool isParent_ = false;
};
