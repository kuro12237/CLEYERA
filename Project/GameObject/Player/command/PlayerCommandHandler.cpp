#include "PlayerCommandHandler.h"

void PlayerCommandHandler::Handler()
{
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		commands_.push(make_unique<PlayerJampCommand>());
	}
	if (Input::PushRShoulder())
	{
		commands_.push(make_unique<PlayerShootCommand>());
	}

	if (IsLJoystickActive())
	{

		commands_.push(make_unique<PlayerMoveCommand>());

	}
}

void PlayerCommandHandler::CommandCoreExec(Player& p)
{
	while (!commands_.empty())
	{
		IPlayerCommand* c = commands_.front().get();
		c->Exec(p);
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
