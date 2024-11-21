#include "PlayerReticleCommandHandler.h"


using namespace Engine;

void PlayerReticleCommandHandler::Handler()
{
	if (IsRJoystickActive())
	{
		commands_.push(make_unique<PlayerReticleMoveCommand>());
	}
}

void PlayerReticleCommandHandler::Exec(PlayerReticle& r)
{
	while (!commands_.empty())
	{
		IPlayerReticleCommand* c = commands_.front().get();
		c->Exec(r);
		commands_.pop();
	}
}

bool PlayerReticleCommandHandler::IsRJoystickActive()
{
	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyRStickPos();
	if (std::abs(Ljoy.x) > joystickThreshold_ || std::abs(Ljoy.y) > joystickThreshold_) {

		return true;
	}
    return false;
}
