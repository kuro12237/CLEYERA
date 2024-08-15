#pragma once

class PlayerBullet;
class IPlayerBulletState
{
public:
	IPlayerBulletState() {};
	virtual ~IPlayerBulletState() {};

	virtual void Initialize(PlayerBullet* p) = 0;

	virtual void Update(PlayerBullet* p) = 0;

private:

};

