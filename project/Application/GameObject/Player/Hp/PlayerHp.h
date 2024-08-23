#pragma once
#include"Sprite/Sprite.h"

class PlayerHp
{
public:
	PlayerHp() {};
	~PlayerHp() {};

	void Initialize(uint32_t hp);

	void Update();

	void Draw2d();

	int32_t &GetHp() { return hpCount_; }

private:

	int32_t hpCount_ = 0;

	unique_ptr<Sprite>sprite_ = nullptr;
	vector<WorldTransform>wTs_{};
	uint32_t texHandle_ = 0;

};
