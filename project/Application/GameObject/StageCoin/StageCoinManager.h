#pragma once
#include"StageCoin.h"
#include"GameObject/ObjectInterface/ManagerComponent.h"

/// <summary>
/// コイン管理クラス
/// </summary>
class StageCoinManager :public INameable,public ManagerComponent
{
public:
	StageCoinManager() {};
	~StageCoinManager() {};

	void Initialize()override;

	void Update()override;

#pragma region Get
	vector<shared_ptr<StageCoin>>GetCoins() { return stageCoins_; }
	int32_t GetCoinsCount() { return coinsCount_; }
#pragma endregion


private:

	GameObjectManager* gameObjectManager_ = nullptr;

	vector<shared_ptr<StageCoin>>stageCoins_ = {};

	int32_t countMax_ = 0;
	int32_t coinsCount_ = 0;

	float animationFlame_ = 0.0f;
	SAnimation::Animation animationData_{};
};
