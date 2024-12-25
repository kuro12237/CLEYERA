#pragma once
#include"EnemyWalk.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IManagerList.h"


/// <summary>
/// 歩く敵の管理クラス
/// </summary>
class EnemyWalkManager :public IManagerList
{
public:
	EnemyWalkManager() {};
	~EnemyWalkManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="data"></param>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

#pragma region Get
	vector<shared_ptr<EnemyWalk>>GetData() { return enemys_; }
#pragma endregion

#pragma region Set
	void SetIsStartFlag(bool f) { isGameStartFlag_ = f; }
	bool GetIsStartFlag() { return isGameStartFlag_; }
#pragma endregion

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	uint32_t enemyCount_ = 0;
	vector<shared_ptr<EnemyWalk>>enemys_;

	bool isGameStartFlag_ = false;
};
