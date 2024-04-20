#pragma once
#include"Game3dObject.h"
#include"Animation/AnimationManager.h"

class Item
{
public:
	Item() {};
	~Item() {};

	void Initialize();

	void Update();

	void Animation();

	void Draw(const CameraData& camera);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_ = {};


	WorldTransform worldTransform_ = {};
	uint32_t animationHandle_ = 0;
	float animationTimer_ = 0.0f;
};
