#include "PlayerStateFall.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateFall::Initialize([[maybe_unused]]Player* p)
{
}

void PlayerStateFall::Update([[maybe_unused]] Player* p)
{
	GameObjectManager* gameObjectManager_ = GameObjectManager::GetInstance();
	SAnimation::Skeleton& skeleton = gameObjectManager_->GetObj3dData(p->INameable::GetName())->GetGameObject()->GetSkeleton();

	uint32_t animationHandle = AnimationManager::GetInstance()->LoadAnimation("JampHuman");
	SAnimation::Animation walkAnimationData_ = AnimationManager::GetInstance()->GetData(animationHandle);
	AnimationManager::ApplyAnimation(skeleton, walkAnimationData_, 0.5f);
	if (p->GetVelocity().y>=0.0f)
	{
		AnimationManager::ApplyAnimation(skeleton, walkAnimationData_, walkAnimationData_.duration);
		p->MarkStateForRemoval<PlayerStateFall>();
	}
}
