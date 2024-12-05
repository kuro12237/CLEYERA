#pragma once

#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// プレイヤーが死んだときのアニメーション
/// </summary>
class PlayerStateDeadAnimation :public IPlayerState
{
public:
	PlayerStateDeadAnimation() {};
	~PlayerStateDeadAnimation() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:
	float deadAnimationFlame_ = 0.0f;
	SAnimation::Animation deadAnimationData_;

	GameObjectManager* gameObjectInstance_ = nullptr;
	string filePath_ = "";

	float flame_ = 0.0f;
	float flameAdd_ = 1.0f / 60.0f;
	float flameMax_ = 1.0f;
};
