#include "PlayerStateWalk.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateWalk::Initialize([[maybe_unused]] Player* p)
{
	uint32_t animationHandle = AnimationManager::GetInstance()->LoadAnimation("Human");
	walkAnimationData_ = AnimationManager::GetInstance()->GetData(animationHandle);
	gameObjectManager_ = GameObjectManager::GetInstance();
}

void PlayerStateWalk::Update([[maybe_unused]] Player* p)
{
	const float speed = 0.2f;
	const float flameAdd = 1.0f / 30.0f;
	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();
	Math::Vector::Vector3 velo = p->GetVelocity();

	velo.x = Ljoy.x * speed;
	p->SetVelocity(velo);
	if (!p->IsInState<PlayerStateJamp>() && !p->IsInState<PlayerStateFall>())
	{
		SAnimation::Skeleton& skeleton = gameObjectManager_->GetObj3dData(p->INameable::GetName())->GetGameObject()->GetSkeleton();

		flame_ += flameAdd * std::abs(Ljoy.x);
		flame_ = std::fmod(flame_, walkAnimationData_.duration);
		AnimationManager::ApplyAnimation(skeleton, walkAnimationData_, flame_);

		//パーティクル
	}
	//状態解除
	if (velo.x == 0.0f)
	{
		p->MarkStateForRemoval<PlayerStateWalk>();
	}

	if (p->IsInState<PlayerStateAim>())
	{
		p->MarkStateForRemoval<PlayerStateWalk>();
	}
}

