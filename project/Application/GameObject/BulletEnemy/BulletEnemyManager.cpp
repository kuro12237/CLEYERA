#include "BulletEnemyManager.h"

void BulletEnemyManager::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();

	const string name = "GunEnemyCore";

	for (uint32_t index = 0; index < uint32_t(gameObjectManager_->GetObj3dDatas().size()); index++)
	{
		string enemyName = "";

		enemyName = name + FormatNumberWithDots(enemyCount_);

		if (gameObjectManager_->GetObj3dDatas().find(enemyName) != gameObjectManager_->GetObj3dDatas().end())
		{
			auto obj = gameObjectManager_->GetObj3dData(enemyName);

			shared_ptr<BulletEnemy>enemyBullet = nullptr;
			enemyBullet = make_shared<BulletEnemy>();
			enemyBullet->INameable::SetName(enemyName);
			enemyBullet->Initialize();

			enemys_.resize(enemyCount_ + 1);
			enemys_[enemyCount_] = move(enemyBullet);
			enemyCount_++;
		}
		else
		{
			break;
		}
	}
}

void BulletEnemyManager::Update()
{
	if (!isGameStartFlag_)
	{
		return;
	}
	for (auto& enemy : enemys_)
	{
		if (enemy)
		{
			enemy->Update();
			//死んだら消す
			if (enemy->GetIsEnd())
			{
				gameObjectManager_ ->ClearObj3dData(enemy->INameable::GetName());
				enemy.reset();
			}
		}
	}
}
