#include "GunEnemyManager.h"

void GunEnemyManager::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();

	const string name = "GunEnemyCore";

	for (uint32_t index = 0; index < uint32_t(gameObjectManager_->GetObj3dDatas().size()); index++)
	{
		string enemyName = "";
		enemyName = name + FormatNumberWithDots(enemyCount_);

		if (gameObjectManager_->GetObj3dDatas().find(enemyName) != gameObjectManager_->GetObj3dDatas().end())
		{
			shared_ptr<GunEnemy>enemyBullet = nullptr;
			enemyBullet = make_shared<GunEnemy>();
			enemyBullet->INameable::SetName(enemyName);
			enemyBullet->Initialize();
			enemyBullet->SetEnemyNumber(enemyCount_);

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

void GunEnemyManager::Update()
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
			if (enemy->GetIsDead())
			{
				gameObjectManager_ ->ClearObj3dData(enemy->INameable::GetName());

				GameObjectManager::GetInstance()->ClearObj3dData("GunEnemyLeft"+FormatNumberWithDots(enemy->GetEnemyNumber()));
				GameObjectManager::GetInstance()->ClearObj3dData("GunEnemyRight"+ FormatNumberWithDots(enemy->GetEnemyNumber()));
				GameObjectManager::GetInstance()->ClearObj3dData("GunEnemyBarrel" + FormatNumberWithDots(enemy->GetEnemyNumber()));

				for (shared_ptr<GunEnemyBullet>& b : enemy->GetBullets())
				{
					if (!b)
					{
						continue;
					}

					gameObjectManager_->ClearObj3dData(b->INameable::GetName());
					b.reset();
				}

				enemy.reset();
			}
		}
	}
}
