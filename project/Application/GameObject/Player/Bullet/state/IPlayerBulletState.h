#pragma once

class PlayerBullet;
/// <summary>
/// 弾の状態インターフェース
/// </summary>
class IPlayerBulletState
{
public:
	IPlayerBulletState() {};
	virtual ~IPlayerBulletState() {};

	virtual void Initialize(PlayerBullet* p) = 0;

	virtual void Update(PlayerBullet* p) = 0;

private:

};

