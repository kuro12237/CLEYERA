#pragma once
#include"GameObject/Player/Reticle/PlayerReticle.h"
#include"IPlayerReticleCommand.h"
#include"PlayerReticleMoveCommand.h"

class PlayerReticleCommandHandler
{
public:
	PlayerReticleCommandHandler() {};
	~PlayerReticleCommandHandler() {};

	void Handler();

	void Exec(PlayerReticle& r);

private:

	bool IsRJoystickActive();

	queue<unique_ptr<IPlayerReticleCommand>>commands_;
	float joystickThreshold_ = 0.2f;
};