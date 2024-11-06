#include "GameSceneUI.h"

using namespace Engine::Transform;
using namespace Engine::Objects;

void GameSceneUI::Initialize()
{
	bottonAction_ = make_unique<GameSceneUIBottonsAction>();
	bottonControl_ = make_unique<GameSceneUIBottonsControl>();

	//joyStickの初期化
	joyStickUis_.resize(joyStickMax_);

	for (size_t i = 0; i < size_t(joyStickMax_); i++)
	{
		joyStickUis_[i].backUi = make_shared<JoyStickBackUI>();
		joyStickUis_[i].stickUi = make_shared<JoyStickUI>();

		sprites_.push_back(joyStickUis_[i].backUi);
		sprites_.push_back(joyStickUis_[i].stickUi);
	}

	string joyStickGropName = "GameSceneJoyStickUI_";
	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_L)].groupName = joyStickGropName;
	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_L)].Initialize(JoyStickLeftRight::Left);

	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_R)].groupName = joyStickGropName;
	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_R)].Initialize(JoyStickLeftRight::Right);

	shared_ptr<BaseBottonUI>bottonA = make_shared<BaseBottonUI>();
	bottonA->Initilaize(joyStickGropName, SceneUIEnum::Botton_A);
	//関数渡す
	bottonA->SetControlActionFunction(std::bind(&GameSceneUIBottonsControl::ControlA, bottonControl_.get()));
	bottonA->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAActive, bottonAction_.get(), std::placeholders::_1));
	bottonA->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAInactive, bottonAction_.get(), std::placeholders::_1));

	bottonUis_.push_back(move(bottonA));

	for (weak_ptr<BaseBottonUI>ui : bottonUis_)
	{
		sprites_.push_back(ui.lock());
	}
}

void GameSceneUI::Update()
{
	//ジョイスティック更新
	for (size_t i = 0; i < size_t(joyStickMax_); i++)
	{
		joyStickUis_[i].backUi->Update();
		joyStickUis_[i].stickUi->Update();
	}
	//ボタン更新
	for (weak_ptr<BaseBottonUI> data : bottonUis_)
	{
		auto it = data.lock();
		it->Update();
	}
}

void GameSceneUI::Draw2d()
{
	for (auto& sprite : sprites_)
	{
		auto it = sprite.lock();
		it->Draw2d();
	}
}

void JoyStickUIData::Initialize(const JoyStickLeftRight& direction)
{
	stickUi->Initilaize(groupName, direction);
	backUi->Initilaize(groupName, direction);
}
