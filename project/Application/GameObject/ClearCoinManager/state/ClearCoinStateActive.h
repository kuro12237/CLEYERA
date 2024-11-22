#pragma once
#include"IClearCoinState.h"
#include"../ClearCoin.h"

/// <summary>
/// coinある時のステート
/// </summary>
class ClearCoinStateActive:public IClearCoinState
{
public:
	ClearCoinStateActive() {};
	~ClearCoinStateActive() {};

	void Initialize()override;

	void Update(ClearCoin* state)override;

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	SAnimation::Animation animationData_{};
	float flame_ = 0.0f;
};
