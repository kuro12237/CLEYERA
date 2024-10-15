#pragma once
#include"GameObject/Player/command/IPlayerCommand.h"
#include"GameObject/Player/Player.h"

/// <summary>
/// •à‚­ƒRƒ}ƒ“ƒh
/// </summary>
class PlayerMoveCommand:public IPlayerCommand
{
public:
	PlayerMoveCommand() {};
	~PlayerMoveCommand() {};

	void Exec(Player& p)override;

private:



};

