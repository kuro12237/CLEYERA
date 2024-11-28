#include "PlayerStateDash.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateDash::Initialize(Player* p)
{
	p;
	uint32_t animationHandle = AnimationManager::GetInstance()->LoadAnimation("PlayerHumanRun");
	walkAnimationData_ = AnimationManager::GetInstance()->GetData(animationHandle);

	gameObjectManager_ = GameObjectManager::GetInstance();
}

void PlayerStateDash::Update(Player* p)
{

	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();

	Math::Vector::Vector3 velo = p->GetVelocity();

	velo.x = Ljoy.x * 0.4f;

	p->SetVelocity(velo);

	if (!p->IsInState<PlayerStateJamp>() && !p->IsInState<PlayerStateFall>())
	{
		//アニメーション再生
		SAnimation::Skeleton& skeleton = gameObjectManager_->GetObj3dData(p->INameable::GetName())->GetGameObject()->GetSkeleton();

		animationFlame_ += 1.0f / 30.0f * std::abs(Ljoy.x);

		animationFlame_ = std::fmod(animationFlame_, walkAnimationData_.duration);
		AnimationManager::ApplyAnimation(skeleton, walkAnimationData_, animationFlame_);

		//パーティクル
		CharacterMoveParticle::GetInstance()->Emit();
	}
	//stateの削除
	if (velo.x == 0.0f)
	{
		p->MarkStateForRemoval<PlayerStateDash>();
	}
}

