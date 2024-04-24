#pragma once
#include"IPlayerGunState.h"


class PlayerGunAttackState :public IPlayerGunState
{
public:
	PlayerGunAttackState() {};
	~PlayerGunAttackState() {};

	void Initialize()override;

	void Update(PlayerGun* gun)override;

private:

};