#pragma once
#include"GameObject/Player/Player.h"
#include"IPlayerState.h"
#include"PlayerNormalState.h"


class PlayerStoneState : public IPlayerState
{
public:
	PlayerStoneState() {};
	~PlayerStoneState() {};

	void Initialize()override;

	void Update(Player* player)override;

private:

	float flame = 0.0f;

	static const uint32_t stateTimerMax_ = 2;
	uint32_t stateTimer_ = 0;
};

