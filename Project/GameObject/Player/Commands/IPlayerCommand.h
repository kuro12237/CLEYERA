#pragma once
#include"GameObject/Player/Player.h"

class Player;
class IPlayerCommand
{
public:

	virtual ~IPlayerCommand() {};

	virtual void Exec(Player& player) = 0;

private:

};