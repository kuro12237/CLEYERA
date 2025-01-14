#include "StageCoinManager.h"

using namespace Engine::Manager;

void StageCoinManager::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();

	this->name_ = "StageCoinManager";
	this->jsonGropName_ = "StageCoinmanager";

	this->CreateJsonData();

	AddJsonItem("CoinMax", countMax_);
	countMax_ = GetJsonItem<int32_t>("CoinMax");

	stageCoins_.resize(countMax_);

	for (int32_t i = 0; i < countMax_; i++)
	{
		stageCoins_[i] = make_shared<StageCoin>();
		stageCoins_[i]->SetCoinNumber(i);
		stageCoins_[i]->Initialize();
	}
	uint32_t animationHandle = AnimationManager::GetInstance()->LoadAnimation("StageCoin");
	animationData_ = AnimationManager::GetInstance()->GetData(animationHandle);
}

void StageCoinManager::Update()
{
	animationFlame_ += 1.0f / 60.0f;

	animationFlame_ = std::fmod(animationFlame_, animationData_.duration);


	for (int32_t i = 0; i < countMax_; i++)
	{
		if (stageCoins_[i])
		{
		
			if (stageCoins_[i]->GetIsDead())
			{

				coinsCount_++;
				GameObjectManager::GetInstance()->ClearObj3dData(stageCoins_[i]->INameable::GetName());
				stageCoins_[i].reset();
				continue;
			}


			auto& skeleton = gameObjectManager_->GetObj3dData(stageCoins_[i]->INameable::GetName())->GetGameObject()->GetSkeleton();

			AnimationManager::ApplyAnimation(skeleton, animationData_, animationFlame_);

			gameObjectManager_->GetObj3dData(stageCoins_[i]->INameable::GetName())->GetGameObject()->SkeletonUpdate();

			stageCoins_[i]->Update();
		}
	}
}
