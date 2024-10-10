#pragma once
#include"Sprite/Sprite.h"

class TitlePushA
{
public:
	TitlePushA() {};
	~TitlePushA() {};

	void Initiaize();

	void Update();

	void Draw();

private:

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t texhandle_ = 0;

	const float kScale_= 0.75f;
	Math::Vector::Vector3 pos_ = { 640.0f,618.0f,0.0f };
};
