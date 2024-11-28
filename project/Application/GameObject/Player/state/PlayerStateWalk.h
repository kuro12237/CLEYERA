#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// プレイヤー歩き状態
/// </summary>
class PlayerStateWalk :public IPlayerState
{
public:
	PlayerStateWalk() {};
	~PlayerStateWalk() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:
	GameObjectManager* gameObjectManager_ = nullptr;
	SAnimation::Animation walkAnimationData_{};
	float flame_ = 0.0f;
};
