#pragma once
#include"GameObject/Player/Reticle/PlayerReticle.h"
#include"IPlayerReticleCommand.h"
#include"PlayerReticleMoveCommand.h"

/// <summary>
/// レティクル仕分けクラス
/// </summary>
class PlayerReticleCommandHandler
{
public:
	PlayerReticleCommandHandler() {};
	~PlayerReticleCommandHandler() {};

	/// <summary>
	/// command作製
	/// </summary>
	void Handler();

	/// <summary>
	/// コマンド実行
	/// </summary>
	/// <param name="r"></param>
	void Exec(PlayerReticle& r);

private:

	bool IsRJoystickActive();

	queue<unique_ptr<IPlayerReticleCommand>>commands_;
	float joystickThreshold_ = 0.2f;
};