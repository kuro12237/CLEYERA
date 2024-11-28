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

	/// <summary>
	/// 回転
	/// </summary>
	/// <param name="velo"></param>
	void RotateControl(const Math::Vector::Vector3 &velo);



	float animationFlame_ = 0.0f;
	GameObjectManager* gameObjectManager_ = nullptr;

	SAnimation::Animation walkAnimationData_ = {};
};
