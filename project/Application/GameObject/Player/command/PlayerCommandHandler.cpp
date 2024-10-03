#include "PlayerCommandHandler.h"

void PlayerCommandHandler::Handler()
{
	//A�{�^��
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		commands_.push(make_unique<PlayerJampCommand>());
	}
	//���X�e�B�b�N���L����
	if (IsLJoystickActive())
	{
		commands_.push(make_unique<PlayerMoveCommand>());
	}

	if (Input::PushRShoulder())
	{
		commands_.push(make_unique<PlayerShootCommand>());
	}

}

void PlayerCommandHandler::CommandsExec(Player& player)
{
	while (!commands_.empty())
	{
		IPlayerCommand* command = commands_.front().get();
		command->Exec(player);
		commands_.pop();
	}
}

bool PlayerCommandHandler::IsLJoystickActive()
{
	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();
	if (std::abs(Ljoy.x) > joystickThreshold_ || std::abs(Ljoy.y) > joystickThreshold_) {

		return true;
	}
	return false;
}
