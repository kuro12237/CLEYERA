#pragma once

class Player;
/// <summary>
/// プレイヤーのコマンドインターフェース
/// </summary>
class IPlayerCommand
{
public:
	IPlayerCommand() {};
	virtual ~IPlayerCommand() {};

	virtual void Exec(Player& p) = 0;

private:

};

