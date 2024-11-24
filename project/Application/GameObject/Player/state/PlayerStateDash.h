#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// プレイヤー走る状態
/// </summary>
class PlayerStateDash :public IPlayerState
{
public:
	PlayerStateDash() {};
	~PlayerStateDash() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

	float flame_ = 0.0f;
	float animationFlame_ = 0.0f;
};
