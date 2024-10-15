#pragma once
#include"GameObject/Player/Reticle/PlayerReticle.h"
#include"IPlayerReticleCommand.h"
#include"PlayerReticleMoveCommand.h"

/// <summary>
/// ���e�B�N���d�����N���X
/// </summary>
class PlayerReticleCommandHandler
{
public:
	PlayerReticleCommandHandler() {};
	~PlayerReticleCommandHandler() {};

	/// <summary>
	/// command�쐻
	/// </summary>
	void Handler();

	/// <summary>
	/// �R�}���h���s
	/// </summary>
	/// <param name="r"></param>
	void Exec(PlayerReticle& r);

private:

	bool IsRJoystickActive();

	queue<unique_ptr<IPlayerReticleCommand>>commands_;
	float joystickThreshold_ = 0.2f;
};