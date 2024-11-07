#include "GameSceneUI.h"

using namespace Engine::Transform;
using namespace Engine::Objects;

void GameSceneUI::Initialize()
{
	//アクション,コントロールクラス初期化
	bottonAction_ = make_unique<GameSceneUIBottonsAction>();
	bottonControl_ = make_unique<GameSceneUIBottonsControl>();

	bottonAction_->Initialize();

	//背景読み込み
	string joyStickBackKey = "GameSceneJoyStickUI_Back_";
	this->KeyCreateEnumNoneUI(joyStickBackKey);

	//L
	string joyStickGropName = "GameSceneJoyStickUI_";
	for (size_t i = 0; i < 2; i++)
	{
		shared_ptr<BaseBottonUI>joyStick = make_shared<BaseBottonUI>();
		if (static_cast<SceneUIEnum>(i)==SceneUIEnum::JoyStick_L)
		{
			joyStick->Initilaize(joyStickGropName, static_cast<SceneUIEnum>(i), std::bind(&GameSceneUIBottonsAction::JoyStickLInitialize, bottonAction_.get(), std::placeholders::_1));
			joyStick->SetUpdateFunction(std::bind(&GameSceneUIBottonsAction::JoyStickLUpdate, bottonAction_.get(), std::placeholders::_1));
		}
		if (static_cast<SceneUIEnum>(i) == SceneUIEnum::JoyStick_R)
		{
			joyStick->Initilaize(joyStickGropName, static_cast<SceneUIEnum>(i), std::bind(&GameSceneUIBottonsAction::JoyStickRInitialize, bottonAction_.get(), std::placeholders::_1));
			joyStick->SetUpdateFunction(std::bind(&GameSceneUIBottonsAction::JoyStickRUpdate, bottonAction_.get(), std::placeholders::_1));
		}
		//関数渡す
		bottonUis_.push_back(move(joyStick));
	}

	string bottonBackKey = "GameSceneBottonBack_";
	this->KeyCreateEnumNoneUI(bottonBackKey);

	//A
	string bottonsGropName = "GameSceneBotton_";
	shared_ptr<BaseBottonUI>bottonA = make_shared<BaseBottonUI>();
	bottonA->Initilaize(bottonsGropName, SceneUIEnum::Botton_A);
	//関数渡す
	bottonA->SetControlActionFunction(std::bind(&GameSceneUIBottonsControl::ControlA, bottonControl_.get()));
	bottonA->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAActive, bottonAction_.get(), std::placeholders::_1));
	bottonA->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAInactive, bottonAction_.get(), std::placeholders::_1));
	bottonUis_.push_back(move(bottonA));

	//RT
	shared_ptr<BaseBottonUI>bottonRT = make_shared<BaseBottonUI>();
	bottonRT->Initilaize(bottonsGropName, SceneUIEnum::Botton_RT);
	//関数渡す
	bottonRT->SetControlActionFunction(std::bind(&GameSceneUIBottonsControl::ControlRT, bottonControl_.get()));
	bottonRT->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRTActive, bottonAction_.get(), std::placeholders::_1));
	bottonRT->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRTInactive, bottonAction_.get(), std::placeholders::_1));
	bottonUis_.push_back(move(bottonRT));

	string textGroupName = "GameSceneText_";
	this->KeyCreateEnumNoneUI(textGroupName);

	PushSpriteData();

}

void GameSceneUI::Update()
{
	//ボタン更新
	for (weak_ptr<BaseBottonUI> data : bottonUis_)
	{
		auto it = data.lock();
		it->Update();
	}
}
