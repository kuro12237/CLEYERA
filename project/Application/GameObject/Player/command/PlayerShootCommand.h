#pragma once
#include"IPlayerCommand.h"
#include"GameObject/Player/Player.h"

/// <summary>
/// ŽËŒ‚ƒRƒ}ƒ“ƒh
/// </summary>
class PlayerShootCommand :public IPlayerCommand
{
public:
	PlayerShootCommand() {};
	~PlayerShootCommand() {};

	void Exec(Player& p)override;

private:

};