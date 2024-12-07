#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"

#include"GunEnemy.h"

/// <summary>
/// 銃の敵管理クラス
/// </summary>
class GunEnemyManager
{
public:
	GunEnemyManager() {};
	~GunEnemyManager() {};

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

	vector<shared_ptr<GunEnemy>>GetGunEnemys() { return enemys_; }

#pragma endregion

#pragma region Set

	void setIsStartFlag(bool flag) { isGameStartFlag_ = flag; }
#pragma endregion


private:

	GameObjectManager* gameObjectManager_ = nullptr;

	uint32_t enemyCount_ = 0;

	vector<shared_ptr<GunEnemy>>enemys_{};


	bool isGameStartFlag_ = false;
};

