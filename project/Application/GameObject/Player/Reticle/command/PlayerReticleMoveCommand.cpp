#include "PlayerReticleMoveCommand.h"

void PlayerReticleMoveCommand::Exec(PlayerReticle& r)
{
	r.Move();
}
