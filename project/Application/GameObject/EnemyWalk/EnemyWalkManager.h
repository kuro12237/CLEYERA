#pragma once
#include"EnemyWalk.h"
#include"Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// �����G�̊Ǘ��N���X
/// </summary>
class EnemyWalkManager
{
public:
	EnemyWalkManager() {};
	~EnemyWalkManager() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="data"></param>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

#pragma region Get
	vector<shared_ptr<EnemyWalk>>GetData() { return enemys_; }
#pragma endregion

#pragma region Set
	void SetStatFlag(bool f) { gameStartFlag_ = f; }
#pragma endregion

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	uint32_t enemyCount_ = 0;
	vector<shared_ptr<EnemyWalk>>enemys_;

	bool gameStartFlag_ = false;
};
