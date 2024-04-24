#include "PlayerInputHandler.h"

void PlayerInputHandler::Handler()
{
	if (Input::PushBotton(XINPUT_GAMEPAD_A))
	{
		commands_.push(make_unique<PlayerJampCommand>());
	}
	if (Input::PushRShoulder())
	{
		commands_.push(make_unique<PlayerGunAttackCommand>());
	}
}

void PlayerInputHandler::CommandsExc(Player& player)
{
	while (!commands_.empty()) {
		IPlayerCommand * c = commands_.front().get();
		c->Exec(player);
		commands_.pop();
	}
}

void PlayerInputHandler::ImGuiUpdate()
{
	ImGui::Text("%d",int32_t(commands_.size()));
}
