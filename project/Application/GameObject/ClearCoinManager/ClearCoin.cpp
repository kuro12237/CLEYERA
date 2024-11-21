#include "ClearCoin.h"

void ClearCoin::Initialize()
{
	cameraPos_ = &gameObjectManager_->GetCameraData("Camera")->GetWorldTransform().transform.translate;
	uint32_t animationHandle = Engine::Manager::AnimationManager::GetInstance()->LoadAnimation("ClearCoinAnimation");
	animationData_ = Engine::Manager::AnimationManager::GetInstance()->GetData(animationHandle);
}

void ClearCoin::Update()
{
	auto& skeleton = gameObjectManager_->GetObj3dData(name_)->GetGameObject()->GetSkeleton();

	flame_ += 1.0f / 60.0f;
	flame_ = fmod(flame_, animationData_.duration);

	Engine::Manager::AnimationManager::ApplyAnimation(skeleton, animationData_,flame_);

	gameObjectManager_->GetObj3dData(name_)->GetGameObject()->SkeletonUpdate();
}
