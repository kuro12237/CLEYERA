#include "PlayerStateDeadAnimation.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateDeadAnimation::Initialize([[maybe_unused]] Player* p)
{
	gameObjectInstance_ = GameObjectManager::GetInstance();

	filePath_ = "FallDown";
	AnimationManager::GetInstance()->LoadAnimation(filePath_);
	deadAnimationData_ = AnimationManager::GetInstance()->GetData(filePath_);
}


void PlayerStateDeadAnimation::Update([[maybe_unused]] Player* p)
{

	const float flameAdd = 1.0f / 30.0f;
	if (deadAnimationFlame_ <= 1.0f) {
		deadAnimationFlame_ += flameAdd;
		deadAnimationFlame_ = std::fmod(deadAnimationFlame_, deadAnimationData_.duration);
	}
	else
	{
		flame_ += flameAdd_;
	}

	if (flame_ >= flameMax_)
	{
		p->SetIsDeadComplite(true);
	}

	SAnimation::Skeleton& skeleton = gameObjectInstance_->GetObj3dData(p->INameable::GetName())->GetGameObject()->GetSkeleton();
	AnimationManager::ApplyAnimation(skeleton, deadAnimationData_, deadAnimationFlame_);
}
