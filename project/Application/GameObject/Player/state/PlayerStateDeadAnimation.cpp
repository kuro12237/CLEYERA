#include "PlayerStateDeadAnimation.h"

void PlayerStateDeadAnimation::Initialize([[maybe_unused]] Player* p)
{
	gameObjectInstance_ = GameObjectManager::GetInstance();

	filePath_ = "FallDown";
	AnimationManager::GetInstance()->LoadAnimation(filePath_);
	walkAnimationData_ = AnimationManager::GetInstance()->GetData(filePath_);
	
}


void PlayerStateDeadAnimation::Update([[maybe_unused]]Player* p)
{
	if (walkAnimationFlame_ <= 1.0f) {
		walkAnimationFlame_ += (1.0f / 30.0f);
		walkAnimationFlame_ = std::fmod(walkAnimationFlame_, walkAnimationData_.duration);
	}
	else
	{
		flame_ += flameAdd_;
	}

	if (flame_ >= flameMax_)
	{
		p->SetIsDeadComplite(true);
	}

	gameObjectInstance_->GetObj3dData(p->INameable::GetName())->GetGameObject()->SkeletonUpdate(filePath_, walkAnimationFlame_);

}