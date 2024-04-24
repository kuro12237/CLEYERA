#pragma once
#include"IPlayerCommand.h"

class PlayerGunAttackCommand :public IPlayerCommand
{
public:
	PlayerGunAttackCommand() {};
	~PlayerGunAttackCommand() {};

	void Exec(Player& player)override;

private:

};