#include "ClearCoinStateActive.h"

void ClearCoinStateActive::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();
	uint32_t animHandle = Engine::Manager::AnimationManager::GetInstance()->LoadAnimation("ClearCoinAnimation");
	animationData_ = Engine::Manager::AnimationManager::GetInstance()->GetData(animHandle);

}

void ClearCoinStateActive::Update([[maybe_unused]]ClearCoin* state)
{
	auto& skeleton = gameObjectManager_->GetObj3dData(state->INameable::GetName())->GetGameObject()->GetSkeleton();

	flame_ += 1.0f / 60.0f;
	flame_ = fmod(flame_, animationData_.duration);

	Engine::Manager::AnimationManager::ApplyAnimation(skeleton, animationData_, flame_);

	gameObjectManager_->GetObj3dData(state->INameable::GetName())->GetGameObject()->SkeletonUpdate();
}
