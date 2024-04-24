#pragma once
#include"IPlayerGunState.h"
#include"GameObject/Player/PlayerGun/PlayerGun.h"

class PlayerGunAttackState :public IPlayerGunState
{
public:
	PlayerGunAttackState() {};
	~PlayerGunAttackState() {};

	void Initialize()override;

	void Update(PlayerGun* gun)override;

private:

	float bulletRate_ = 0.0f;
	const float bulletRateMax_ = 4.0f;

};