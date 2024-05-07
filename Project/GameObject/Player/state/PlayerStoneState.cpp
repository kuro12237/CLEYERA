#include "PlayerStoneState.h"

void PlayerStoneState::Initialize()
{
}

void PlayerStoneState::Update(Player* player)
{
	stateTimer_ += DeltaTimer(flame);

	player->SetBehavior(Stone);
	player->SetGrayFactor(1.0f);

	if (stateTimer_ >= stateTimerMax_)
	{
		player->SetGrayFactor(0.0f);
		player->ChangeState(make_unique<PlayerNormaState>());
		return;
	}

}
