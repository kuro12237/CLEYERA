#include "PlayerStateJamp.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateJamp::Initialize(Player* p)
{
	uint32_t animationHandle = AnimationManager::GetInstance()->LoadAnimation("JampHuman");
	jampAnimationData_ = AnimationManager::GetInstance()->GetData(animationHandle);

	const float jampMax = 1.0f;
	Math::Vector::Vector3 velo = p->GetVelocity();
	velo.y = jampMax;
	p->SetVelocity(velo);
}

void PlayerStateJamp::Update([[maybe_unused]]Player* p)
{
	const float flame = 0.5f;
	GameObjectManager* gameObjectManager_ = GameObjectManager::GetInstance();
	SAnimation::Skeleton& skeleton = gameObjectManager_->GetObj3dData(p->INameable::GetName())->GetGameObject()->GetSkeleton();

	AnimationManager::ApplyAnimation(skeleton, jampAnimationData_, flame);

	if (p->IsInState<PlayerStateJamp>() && p->GetVelocity().y <= 0.0f)
	{
		p->MarkStateForRemoval<PlayerStateJamp>();
		if (!p->IsInState<PlayerStateFall>())
		{
			p->AddState<PlayerStateFall>();
		}
	}
}
