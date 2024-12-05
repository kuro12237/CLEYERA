#include "ClearCharacter.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void ClearCharacter::Initialize()
{
	name_ = "Character";
	uint32_t animHandle= AnimationManager::GetInstance()->LoadAnimation("ClearHumanAnimation_01");
	animationData_ = AnimationManager::GetInstance()->GetData(animHandle);
}

void ClearCharacter::Update()
{
	const float addFlame = 1.0f / 60.0f;
	animFlame_ += addFlame;
    animFlame_ = std::fmod(animFlame_, animationData_.duration);

	SAnimation::Skeleton& skeleton = gameObjectManager_->GetObj3dData(name_)->GetGameObject()->GetSkeleton();

	AnimationManager::ApplyAnimation(skeleton, animationData_, animFlame_);

	gameObjectManager_->GetObj3dData(name_)->GetGameObject()->SkeletonUpdate();

}
