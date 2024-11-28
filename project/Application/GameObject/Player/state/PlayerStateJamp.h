#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// プレイヤージャンプ状態
/// </summary>
class PlayerStateJamp :public IPlayerState
{
public:
	PlayerStateJamp() {};
	~PlayerStateJamp() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:
	float jampAnimationFlame_ = 0.0f;
	SAnimation::Animation jampAnimationData_;

};
