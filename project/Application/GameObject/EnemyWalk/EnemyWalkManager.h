#pragma once
#include"EnemyWalk.h"
#include"Utility/ObjectManager/GameObjectManager.h"

class EnemyWalkManager
{
public:
	EnemyWalkManager() {};
	~EnemyWalkManager() {};

	void Initialize(GameObjectManager *data);

	void Update();

	void PushBack();

#pragma region Get

	vector<shared_ptr<EnemyWalk>>GetData() { return enemys_; }

#pragma endregion

#pragma region Set

	void SetStatFlag(bool f) { gameStartFlag_ = f; }

#pragma endregion


private:

	uint32_t enemyCount_ = 0;
	vector<shared_ptr<EnemyWalk>>enemys_;

	bool gameStartFlag_ = false;
};
