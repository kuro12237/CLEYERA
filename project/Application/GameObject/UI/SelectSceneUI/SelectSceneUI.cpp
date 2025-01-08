#include "SelectSceneUI.h"

void SelectSceneUI::Initialize()
{
	//アクション,コントロールクラス初期化
	bottonAction_ = make_unique<GameSceneUIBottonsAction>();
	bottonAction_->Initialize();

	//背景読み込み
	string joyStickBackKey = "SelectSceneJoyStickUI_Back_";
	this->KeyCreateEnumNoneUI(joyStickBackKey);

	//L
	string joyStickGropName = "SelectSceneJoyStickUI_";
	for (size_t i = 0; i < 2; i++)
	{
		shared_ptr<BaseBottonUI>joyStick = make_shared<BaseBottonUI>();
		if (static_cast<SceneUIEnum>(i) == SceneUIEnum::JoyStick_L)
		{
			joyStick->Initialize(joyStickGropName, static_cast<SceneUIEnum>(i));
			joyStick->SetUpdateFunction(std::bind(&GameSceneUIBottonsAction::JoyStickLUpdate, bottonAction_.get(), std::placeholders::_1));
		}
		if (static_cast<SceneUIEnum>(i) == SceneUIEnum::JoyStick_R)
		{
			joyStick->Initialize(joyStickGropName, static_cast<SceneUIEnum>(i));
			joyStick->SetUpdateFunction(std::bind(&GameSceneUIBottonsAction::JoyStickRUpdate, bottonAction_.get(), std::placeholders::_1));
		}
		//関数渡す
		this->PushUiMapData(joyStick);

	}

	string bottonBackKey = "SelectSceneBottonBack_";
	this->KeyCreateEnumNoneUI(bottonBackKey);

	//A
	string bottonsGropName = "SelectSceneBotton_";
	shared_ptr<BaseBottonUI>bottonA = make_shared<BaseBottonUI>();
	bottonA->Initialize(bottonsGropName, SceneUIEnum::Botton_A);
	//関数渡す
	bottonA->SetControlActionFunction(std::bind(&GameSceneUIBottonsAction::BottonA, bottonAction_.get()));
	bottonA->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAActive, bottonAction_.get(), std::placeholders::_1));
	bottonA->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAInactive, bottonAction_.get(), std::placeholders::_1));

	this->PushUiMapData(bottonA);

	//RT
	shared_ptr<BaseBottonUI>bottonRT = make_shared<BaseBottonUI>();
	bottonRT->Initialize(bottonsGropName, SceneUIEnum::Botton_RT);
	//関数渡す
	bottonRT->SetControlActionFunction(std::bind(&GameSceneUIBottonsAction::BottonRT, bottonAction_.get()));
	bottonRT->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRTActive, bottonAction_.get(), std::placeholders::_1));
	bottonRT->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRTInactive, bottonAction_.get(), std::placeholders::_1));
	this->PushUiMapData(bottonRT);
	//RB
	shared_ptr<BaseBottonUI>bottonRB = make_shared<BaseBottonUI>();
	bottonRB->Initialize(bottonsGropName, SceneUIEnum::Botton_RB);
	//関数渡す
	bottonRB->SetControlActionFunction(std::bind(&GameSceneUIBottonsAction::BottonRB, bottonAction_.get()));
	bottonRB->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRBActive, bottonAction_.get(), std::placeholders::_1));
	bottonRB->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRBInactive, bottonAction_.get(), std::placeholders::_1));
	this->PushUiMapData(bottonRB);

	string textGroupName = "SelectSceneText_";
	this->KeyCreateEnumNoneUI(textGroupName);

	PushSpriteData();
}
