#pragma once
#include"Sprite/Sprite.h"

class TitleName
{
public:
	TitleName() {};
	~TitleName() {};

	void Initialize();

	void Update();

	void Draw();

private:

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t texHandle_ = 0;

};
