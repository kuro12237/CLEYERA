#pragma once
#include"Cleyera.h"

class StartCount
{
public:
	StartCount() {};
	~StartCount() {};

	void Initialize();

	void Update();

	void Draw2d();

#pragma region Get

	bool GetStartFlag() { return startFlag; };
#pragma endregion

private:

	unique_ptr<Sprite>numberSprite_ = nullptr;
	WorldTransform numberWorldTransform_ = {};

	uint32_t numberTex_ = 0;

	float numberAnimationFlame_ = 0.0f;

	uint32_t count = 0;

	bool startFlag = false;
	bool countUpdateFlag_ = false;
	bool countDrawFlag_ = false;
};