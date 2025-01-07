#include "PlayerCommandHandler.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerCommandHandler::Handler()
{
	//左スティックが有効か
	if (IsLJoystickActive())
	{
		commands_.push(make_unique<PlayerMoveCommand>());
	}
	if (IsLJoystickActive()&& Input::PushBotton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		commands_.push(make_unique<PlayerDashMoveCommand>());
	}

	//Aボタン
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		commands_.push(make_unique<PlayerJampCommand>());
	}
	if (Input::PushRShoulder())
	{
		commands_.push(make_unique<PlayerShootCommand>());
	}

	if (Input::GetJoyRActive())
	{
		commands_.push(make_unique<PlayerAimCommand>());
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

	Math::Vector::Vector2 Ljoy = Engine::Input::GetInstance()->GetJoyLStickPos();
	if (std::abs(Ljoy.x) > joystickThreshold_ || std::abs(Ljoy.y) > joystickThreshold_) {

		return true;
	}
	return false;
}
