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

};
