#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// プレイヤー照準状態
/// </summary>
class PlayerStateAim :public IPlayerState
{
public:
	PlayerStateAim() {};
	~PlayerStateAim() {};


	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

	Math::Vector::Vector3 AimRotate(float veloX);

};

