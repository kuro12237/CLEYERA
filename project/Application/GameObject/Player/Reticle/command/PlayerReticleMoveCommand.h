#pragma once
#include"IPlayerReticleCommand.h"
#include"GameObject/Player/Reticle/PlayerReticle.h"

/// <summary>
/// レティクル操作
/// </summary>
class PlayerReticleMoveCommand: public IPlayerReticleCommand
{
public:
	PlayerReticleMoveCommand() {};
	~PlayerReticleMoveCommand() {};

	void Exec(PlayerReticle& r)override;

private:

};

