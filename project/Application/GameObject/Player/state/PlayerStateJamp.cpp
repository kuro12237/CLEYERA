#include "PlayerStateJamp.h"

void PlayerStateJamp::Initialize(Player* p)
{
	const float jampMax = 0.35f;
	Math::Vector::Vector3 velo = p->GetVelocity();
	velo.y = jampMax;
	p->SetVelocity(velo);
}

void PlayerStateJamp::Update([[maybe_unused]]Player* p)
{
	GameObjectManager* gameObjectManager_ = GameObjectManager::GetInstance();
	SAnimation::Skeleton& skeleton = gameObjectManager_->GetObj3dData(p->INameable::GetName())->GetGameObject()->GetSkeleton();

	uint32_t animationHandle = AnimationManager::GetInstance()->LoadAnimation("JampHuman");
	SAnimation::Animation walkAnimationData_ = AnimationManager::GetInstance()->GetData(animationHandle);
	AnimationManager::ApplyAnimation(skeleton, walkAnimationData_, 0.5f);
}
