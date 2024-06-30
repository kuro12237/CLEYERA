#pragma once
#include"IPlayerBulletState.h"
#include"GameObject/Player/Bullet/PlayerBullet.h"

class PlayerBulletStateNone:public IPlayerBulletState
{
public:
	PlayerBulletStateNone() {};
	~PlayerBulletStateNone() {};

	void Initialize(PlayerBullet* p)override;

	void Update(PlayerBullet* p)override;

private:

};

