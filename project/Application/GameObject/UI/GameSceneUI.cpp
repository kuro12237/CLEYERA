#include "GameSceneUI.h"

using namespace Engine::Transform;
using namespace Engine::Objects;

void GameSceneUI::Initialize()
{
	//joyStick�̏�����

	joyStickUis_.resize(joyStickMax_);

	for (size_t i = 0; i < size_t(joyStickMax_); i++)
	{
		joyStickUis_[i].backUi = make_shared<JoyStickBackUI>();
		joyStickUis_[i].stickUi = make_shared<JoyStickUI>();

		sprites_.push_back(joyStickUis_[i].backUi);
		sprites_.push_back(joyStickUis_[i].stickUi);
	}

	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_L)].stickUi->Initilaize("L");
	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_L)].backUi->Initilaize("L");

	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_R)].stickUi->Initilaize("R");
	joyStickUis_[static_cast<int>(GameSceneUIEnum::JoyStick_R)].backUi->Initilaize("R");

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
