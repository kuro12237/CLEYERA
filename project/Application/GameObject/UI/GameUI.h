#pragma once
#include"Sprite/Sprite.h"


class GameUI
{
public:
	GameUI() {};
	~GameUI() {};

	void Initialize();

	void Update();

	void Draw2d();

private:

	unique_ptr<Sprite>bottonASprite_ = nullptr;
	WorldTransform bottonAwT_ = {};
	uint32_t bottonATexhandle_ = 0;

};
