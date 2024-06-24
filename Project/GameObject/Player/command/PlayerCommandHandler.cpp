#include "PlayerCommandHandler.h"

void PlayerCommandHandler::Handler()
{
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		commands_.push(make_unique<PlayerJampCommand>());
	}
}

void PlayerCommandHandler::CommandExec(Player& p)
{
	while (!commands_.empty())
	{
		IPlayerCommand* c = commands_.front().get();
		c->Exec(p);
		commands_.pop();

	}

}
