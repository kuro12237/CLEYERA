#pragma once
#include"IPlayerGunState.h"


class PlayerGunReloadState:public IPlayerGunState
{
public:
	PlayerGunReloadState() {};
	~PlayerGunReloadState() {};

	void Initialize()override;

	void Update(PlayerGun* gun)override;

private:

};