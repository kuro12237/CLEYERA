#pragma once
#include"IPlayerGunState.h"
#include"GameObject/Player/PlayerGun/PlayerGun.h"
#include"Utility/DeltaTimer/DeltaTimer.h"

class PlayerGunReloadState:public IPlayerGunState
{
public:
	PlayerGunReloadState() {};
	~PlayerGunReloadState() {};

	void Initialize()override;

	void Update(PlayerGun* gun)override;

private:

	uint32_t timer_ = 0;
	uint32_t timerMax = 2;
	float flame_ = 0.0f;
};