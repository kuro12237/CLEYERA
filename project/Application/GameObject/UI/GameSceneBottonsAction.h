#pragma once
#include"GameSceneBottonUI/BaseBottonUI.h"

#include"BottonsActions/GameSceneBottonA.h"
#include"BottonsActions/GameSceneBottonRT.h"

class GameSceneUIBottonsAction
{
public:
	GameSceneUIBottonsAction() {};
	~GameSceneUIBottonsAction() {};

	void Initialize();

	///UIÇÃÉäÉAÉNÉVÉáÉìèàóù
#pragma region 

	void BottonAActive(BaseBottonUI&ui);
	void BottonAInactive(BaseBottonUI& ui);

	void BottonRTActive(BaseBottonUI& ui);
	void BottonRTInactive(BaseBottonUI& ui);

#pragma endregion


private:

	unique_ptr<GameSceneUIBottonA>bottonA_ = nullptr;
	unique_ptr<GameSceneUIBottonRT>bottonRT_ = nullptr;

};
