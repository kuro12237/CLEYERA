#pragma once
#include"GameObject/Player/command/IPlayerCommand.h"
#include"GameObject/Player/Player.h"

/// <summary>
/// 走るコマンド
/// </summary>
class PlayerDashMoveCommand :public IPlayerCommand
{
public:
	PlayerDashMoveCommand() {};
	~PlayerDashMoveCommand() {};

	void Exec(Player& p)override;

private:



};