#pragma once
#include"GameObject/Player/command/IPlayerCommand.h"
#include"GameObject/Player/Player.h"


/// <summary>
/// 照準コマンド
/// </summary>
class PlayerAimCommand :public IPlayerCommand
{
public:
	PlayerAimCommand() {};
	~PlayerAimCommand() {};

	void Exec(Player& p)override;

private:



};