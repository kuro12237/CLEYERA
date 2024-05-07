#include "PlayerNormalState.h"

void PlayerNormaState::Initialize()
{
}

void PlayerNormaState::Update(Player* player)
{
	player->SetBehavior(Normal);
	player->Move();
}
