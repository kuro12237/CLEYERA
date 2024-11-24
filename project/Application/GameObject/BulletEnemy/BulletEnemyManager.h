#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"

#include"BulletEnemy.h"

class BulletEnemyManager
{
public:
	BulletEnemyManager() {};
	~BulletEnemyManager() {};

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

	vector<shared_ptr<BulletEnemy>>GetBulletEnemys() { return enemys_; }

#pragma endregion

#pragma region Set

	void setIsStartFlag(bool flag) { isGameStartFlag_ = flag; }
#pragma endregion


private:

	GameObjectManager* gameObjectManager_ = nullptr;

	uint32_t enemyCount_ = 0;

	vector<shared_ptr<BulletEnemy>>enemys_{};


	bool isGameStartFlag_ = false;
};

