#include "PlayerGunReloadState.h"

void PlayerGunReloadState::Initialize()
{
	stateNo = RELOAD;
}

void PlayerGunReloadState::Update(PlayerGun* gun)
{
	timer_ += DeltaTimer(flame_);

	if (timer_ >= timerMax)
	{
		gun->BulletCountReset();
		gun->ChangeState(STAND);
	}
}
