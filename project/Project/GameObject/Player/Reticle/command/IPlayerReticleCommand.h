#pragma once

class PlayerReticle;
class IPlayerReticleCommand
{
public:
	IPlayerReticleCommand() {};
	virtual ~IPlayerReticleCommand() {};

	virtual void Exec(PlayerReticle& r) = 0;

private:


};
