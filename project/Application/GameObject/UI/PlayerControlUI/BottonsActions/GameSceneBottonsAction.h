#pragma once
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

#include"GameSceneBottonA.h"
#include"GameSceneBottonRT.h"
#include"GameSceneBottonRB.h"
#include"GameSceneJoyStick.h"

class GameSceneUIBottonsAction
{
public:
	GameSceneUIBottonsAction() {};
	~GameSceneUIBottonsAction() {};

	void Initialize();

	///UIのリアクション処理
#pragma region 

	void BottonAActive(BaseBottonUI& ui);
	void BottonAInactive(BaseBottonUI& ui);
	
	void BottonRTActive(BaseBottonUI& ui);
	void BottonRTInactive(BaseBottonUI& ui);

	void BottonRBActive(BaseBottonUI& ui);
	void BottonRBInactive(BaseBottonUI& ui);

	void JoyStickLInitialize(BaseBottonUI& ui);
	void JoyStickLUpdate(BaseBottonUI& ui);

	void JoyStickRInitialize(BaseBottonUI& ui);
	void JoyStickRUpdate(BaseBottonUI& ui);

	bool BottonA() { return bottonA_->ControlA(); }
	bool BottonRT() { return bottonRT_->ControlRT(); }
	bool BottonRB() { return bottonRB_->ControlRB(); }

#pragma endregion
	

private:

	unique_ptr<GameSceneUIBottonA>bottonA_ = nullptr;
	unique_ptr<GameSceneUIBottonRT>bottonRT_ = nullptr;
	unique_ptr<GameSceneUIBottonRB>bottonRB_ = nullptr;

	static const uint32_t joystickMax_ = 2;
	array<unique_ptr<GameSceneJoyStick>, joystickMax_>joySticks_;

};
