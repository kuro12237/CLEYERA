#include "GameSceneUI.h"

using namespace Engine::Transform;
using namespace Engine::Objects;

void GameSceneUI::Initialize()
{
	//joyStickÇÃèâä˙âª
	joyStickUis_.resize(joyStickMax_);

	for (size_t i = 0; i < size_t(joyStickMax_); i++)
	{
		joyStickUis_[i].backUi = make_shared<JoyStickBackUI>();
		joyStickUis_[i].stickUi = make_shared<JoyStickUI>();

		sprites_.push_back(joyStickUis_[i].backUi);
		sprites_.push_back(joyStickUis_[i].stickUi);
	}

	string joyStickGropName = "GameSceneJoyStickUI_";
	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_L)].groupName = joyStickGropName;
	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_L)].Initialize(JoyStickLeftRight::Left);

	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_R)].groupName = joyStickGropName;
	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_R)].Initialize(JoyStickLeftRight::Right);

}

void GameSceneUI::Update()
{
	for (size_t i = 0; i < size_t(joyStickMax_); i++)
	{
		joyStickUis_[i].backUi->Update();
		joyStickUis_[i].stickUi->Update();
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
