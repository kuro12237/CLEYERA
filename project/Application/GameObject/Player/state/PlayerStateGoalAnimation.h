#pragma once
#include"GameObject/Player/Player.h"
#include"GameObject/Player/state/IPlayerState.h"

class PlayerStateGoalAnimation :public IPlayerState
{
public:
	PlayerStateGoalAnimation() {};
	~PlayerStateGoalAnimation () {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

	string GoalName_ = "Goal";

	Math::Vector::Vector3  startPos_ = {};
	Math::Vector::Vector3 endPos_ = {};
	float t = 0.0f;
};