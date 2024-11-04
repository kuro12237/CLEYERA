#pragma once
#include"IPlayerState.h"
#include"../Player.h"

#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"
#include"Utility/LerpMotion/LerpMotion.h"

/// <summary>
/// プレイヤーワープ中
/// </summary>
class PlayerStateWarpMove :public IPlayerState
{
public:
	PlayerStateWarpMove() {};
	~PlayerStateWarpMove() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

	float kFlame_ = 60.0f;
	RailData railData_ = {};

	unique_ptr<LerpMotion>lerpMotion_ = nullptr;
	Math::Vector::Vector3 prevPos_ = {};
	uint32_t prevModelHandle_ = 0;
};
