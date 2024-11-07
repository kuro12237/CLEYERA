#pragma once
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

#include"GameSceneBottonA.h"
#include"GameSceneBottonRT.h"
#include"GameSceneJoyStick.h"

class GameSceneUIBottonsAction
{
public:
	GameSceneUIBottonsAction() {};
	~GameSceneUIBottonsAction() {};

	void Initialize();

	///UIÇÃÉäÉAÉNÉVÉáÉìèàóù
#pragma region 

	void BottonAActive(BaseBottonUI& ui);
	void BottonAInactive(BaseBottonUI& ui);

	void BottonRTActive(BaseBottonUI& ui);
	void BottonRTInactive(BaseBottonUI& ui);

	void JoyStickLInitialize(BaseBottonUI& ui);
	void JoyStickLUpdate(BaseBottonUI& ui);

	void JoyStickRInitialize(BaseBottonUI& ui);
	void JoyStickRUpdate(BaseBottonUI& ui);
#pragma endregion


private:

	unique_ptr<GameSceneUIBottonA>bottonA_ = nullptr;
	unique_ptr<GameSceneUIBottonRT>bottonRT_ = nullptr;

	static const uint32_t joystickMax_ = 2;
	array<unique_ptr<GameSceneJoyStick>, joystickMax_>joySticks_;

};
