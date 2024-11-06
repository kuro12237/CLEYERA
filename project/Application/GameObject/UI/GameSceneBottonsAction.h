#pragma once
#include"GameSceneBottonUI/BaseBottonUI.h"
#include"BottonsActions/GameSceneBottonA.h"

class GameSceneUIBottonsAction
{
public:
	GameSceneUIBottonsAction() {};
	~GameSceneUIBottonsAction() {};

	void Initialize();

	void BottonAActive(BaseBottonUI&ui);
	void BottonAInactive(BaseBottonUI& ui);

private:

	unique_ptr<GameSceneUIBottonA>bottonA_ = nullptr;

};
