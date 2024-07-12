#pragma once
#include"EnemyWalk.h"
#include"GameObject/ObjectManager/GameObjectManager.h"

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

private:

	uint32_t enemyCount_ = 0;
	vector<shared_ptr<EnemyWalk>>enemys_;

};
