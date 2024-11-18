#pragma once
#include"StageCoin.h"

/// <summary>
/// コイン管理クラス
/// </summary>
class StageCoinManager:public INameable,public IJsonHandler
{
public:
	StageCoinManager() {};
	~StageCoinManager() {};

	void Initialize();

	void Update();

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	vector<shared_ptr<StageCoin>>stageCoins_ = {};

	int32_t countMax_ = 0;

	float animationFlame_ = 0.0f;
	SAnimation::Animation animationData_{};
};
