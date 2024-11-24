#include "PlayerStateDash.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateDash::Initialize(Player* p)
{
	p;
}

void PlayerStateDash::Update(Player* p)
{
	auto& rotate = GameObjectManager::GetInstance()->GetObj3dData(p->INameable::GetName())->GetWorldTransform().transform.rotate;

	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();

	float joystickThreshold_ = 0.2f;
	if (std::abs(Ljoy.x) < joystickThreshold_ && std::abs(Ljoy.y) < joystickThreshold_)
	{
		p->MarkStateForRemoval<PlayerStateDash>();
	}

	Math::Vector::Vector3 velo = p->GetVelocity();
	velo.x = Ljoy.x * 0.4f;
	p->SetVelocity(velo);

	//右
	const float degrees = 90.0f;
	float radian = 0.0f;
	if (velo.x > 0.0f)
	{
		radian = Math::Vector::degreesToRadians(degrees);
	}
	//左
	if (velo.x < 0.0f)
	{
		radian = Math::Vector::degreesToRadians(-degrees);
	}

	rotate.y = radian;

	if (!p->IsInState<PlayerStateJamp>() && !p->IsInState<PlayerStateFall>())
	{
		GameObjectManager* gameObjectManager_ = GameObjectManager::GetInstance();
		SAnimation::Skeleton& skeleton = gameObjectManager_->GetObj3dData(p->INameable::GetName())->GetGameObject()->GetSkeleton();

		uint32_t animationHandle = AnimationManager::GetInstance()->LoadAnimation("PlayerHumanRun");
		SAnimation::Animation walkAnimationData_ = AnimationManager::GetInstance()->GetData(animationHandle);

		animationFlame_ = std::fmod(animationFlame_, walkAnimationData_.duration);

		animationFlame_ += 1.0f / 30.0f;

		AnimationManager::ApplyAnimation(skeleton, walkAnimationData_, animationFlame_);

		//パーティクル
		CharacterMoveParticle::GetInstance()->Emit();
	}
}
