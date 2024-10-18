#pragma once
#include"EnemyWalk.h"
#include"Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// 歩く敵の管理クラス
/// </summary>
class EnemyWalkManager
{
public:
	EnemyWalkManager() {};
	~EnemyWalkManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="data"></param>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Get
	vector<shared_ptr<EnemyWalk>>GetData() { return enemys_; }
#pragma endregion

#pragma region Set
	void SetIsStartFlag(bool f) { isGameStartFlag_ = f; }
#pragma endregion

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	uint32_t enemyCount_ = 0;
	vector<shared_ptr<EnemyWalk>>enemys_;

	bool isGameStartFlag_ = false;
};
