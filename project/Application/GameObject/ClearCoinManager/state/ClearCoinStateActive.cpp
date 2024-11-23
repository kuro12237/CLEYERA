#include "ClearCoinStateActive.h"

void ClearCoinStateActive::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();

	uint32_t animHandle = Engine::Manager::AnimationManager::GetInstance()->LoadAnimation("ClearCoinAnimation");
	animationData_ = Engine::Manager::AnimationManager::GetInstance()->GetData(animHandle);

}

void ClearCoinStateActive::Update([[maybe_unused]] ClearCoin* state)
{
	if (flame_ >= animationData_.duration)
	{
		state->SetIsEnd(true);
		state->ChangeState(nullptr);
	}
	else
	{
		gameObjectManager_->GetObj3dData(state->INameable::GetName())->SetIsDraw(true);

		auto& skeleton = gameObjectManager_->GetObj3dData(state->INameable::GetName())->GetGameObject()->GetSkeleton();

		flame_ += 1.0f / 10.0f;

		Engine::Manager::AnimationManager::ApplyAnimation(skeleton, animationData_, flame_);
		gameObjectManager_->GetObj3dData(state->INameable::GetName())->GetGameObject()->SkeletonUpdate();
	}
}
