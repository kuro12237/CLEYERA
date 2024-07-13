#include "EnemyWalkManager.h"

void EnemyWalkManager::Initialize(GameObjectManager* data)
{
	const string name = "EnemyWalk_";

	for (uint32_t Count_ = 0; Count_ < uint32_t(data->GetObj3dDatas().size()); Count_++)
	{
		string count = to_string(enemyCount_);

		if (data->GetObj3dDatas().find(name + count) != data->GetObj3dDatas().end())
		{
			auto obj = data->GetObj3dData(name + count);

			shared_ptr<EnemyWalk>enemyWalk = nullptr;
			enemyWalk = make_shared<EnemyWalk>();
			enemyWalk->SetName(name+count);
			enemyWalk->Initialize();
			enemyWalk->SetName(name + count);
			enemyWalk->GetData(GameObjectManager::GetInstance());
			enemys_.resize(enemyCount_+1);
			enemys_[enemyCount_] = (enemyWalk);
			enemyCount_++;
		}
		else
		{
			break;
		}
	}

}

void EnemyWalkManager::Update()
{
	for (auto& enemy : enemys_)
	{
		if (enemy)
		{
			enemy->Update();
			GameObjectManager::GetInstance()->ObjDataUpdate(enemy.get());
			//Ž€‚ñ‚¾‚çÁ‚·
			if (enemy->GetIsDead())
			{
				GameObjectManager::GetInstance()->ClearObj3dData(enemy->GetName());
				enemy.reset();
			}
		}
	}
}
