#pragma once
#include"IPlayerBulletState.h"
#include"GameObject/Player/Bullet/PlayerBullet.h"

/// <summary>
/// �ʏ�
/// </summary>
class PlayerBulletStateNone:public IPlayerBulletState
{
public:
	PlayerBulletStateNone() {};
	~PlayerBulletStateNone() {};

	void Initialize(PlayerBullet* p)override;

	void Update(PlayerBullet* p)override;

private:

};

