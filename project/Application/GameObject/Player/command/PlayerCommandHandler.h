#pragma once
#include"GameObject/Player/Player.h"

#include"PlayerJampCommand.h"
#include"PlayerMoveCommand.h"
#include"PlayerShootCommand.h"
#include"playerDashMoveCommand.h"
#include"PlayerAimCommand.h"

/// <summary>
/// プレイヤー操作仕分け
/// </summary>
class PlayerCommandHandler
{
public:
	PlayerCommandHandler() {};
	~PlayerCommandHandler() {};

	/// <summary>
	/// クラス作製
	/// </summary>
	void Handler();

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player"></param>
	void CommandsExec(Player& player);

private:

	/// <summary>
	/// Lスティックが使えるか
	/// </summary>
	/// <returns></returns>
	bool IsLJoystickActive();

	queue<unique_ptr<IPlayerCommand>>commands_;

	float joystickThreshold_ = 0.2f;
};