#include "EnemyWalkManager.h"

void EnemyWalkManager::Initialize(GameObjectManager* data)
{
	const string name = "EnemyWalk";

	for (uint32_t Count_ = 0; Count_ < uint32_t(data->GetObj3dDatas().size()); Count_++)
	{
		string count = to_string(enemyCount_);

		string enemyName = "";
		if (count == "0")
		{
			enemyName = name;
		}else{
			enemyName = name + "." + string(3 - to_string(enemyCount_).length(), '0') + to_string(enemyCount_);
		}

		if (data->GetObj3dDatas().find(enemyName) != data->GetObj3dDatas().end())
		{
			auto obj = data->GetObj3dData(enemyName);

			shared_ptr<EnemyWalk>enemyWalk = nullptr;
			enemyWalk = make_shared<EnemyWalk>();
			enemyWalk->SetName(enemyName);
			enemyWalk->Initialize();

			enemys_.resize(enemyCount_ + 1);
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
	if (!gameStartFlag_)
	{
		return;
	}
	for (auto& enemy : enemys_)
	{
		if (enemy)
		{
			enemy->Update();
			//Ž€‚ñ‚¾‚çÁ‚·
			if (enemy->GetIsEnd())
			{
				GameObjectManager::GetInstance()->ClearObj3dData(enemy->GetName());
				enemy.reset();
			}
		}
	}
}
