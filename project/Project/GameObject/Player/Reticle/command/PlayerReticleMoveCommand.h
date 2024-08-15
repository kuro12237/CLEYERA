#pragma once
#include"IPlayerReticleCommand.h"
#include"GameObject/Player/Reticle/PlayerReticle.h"

class PlayerReticleMoveCommand: public IPlayerReticleCommand
{
public:
	PlayerReticleMoveCommand() {};
	~PlayerReticleMoveCommand() {};

	void Exec(PlayerReticle& r)override;

private:

};

