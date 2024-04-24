#pragma once
#include"IPlayerGunState.h"


class PlayerGunStandState :public IPlayerGunState
{
public:
	PlayerGunStandState() {};
	~PlayerGunStandState() {};

	void Initialize()override;

	void Update(PlayerGun* gun)override;

private:

};