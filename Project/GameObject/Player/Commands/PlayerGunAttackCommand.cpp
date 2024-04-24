#include "PlayerGunAttackCommand.h"
#include"GameObject/Player/Player.h"

void PlayerGunAttackCommand::Exec(Player& player)
{
	player.GunAttack();
}
