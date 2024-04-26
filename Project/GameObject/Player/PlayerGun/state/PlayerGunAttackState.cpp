#include "PlayerGunAttackState.h"


void PlayerGunAttackState::Initialize()
{
	stateNo = ATTACK;
}

void PlayerGunAttackState::Update(PlayerGun* gun)
{
	gun;
	bulletRate_++;
	if (bulletRate_ >= bulletRateMax_)
	{
		const Math::Vector::Vector2 randomSize = { -0.5f,0.5f };
		Math::Vector::Vector3 randomPos = {
			RandomGenerator::GetInstance()->GetFloat(randomSize.x, randomSize.y),
			RandomGenerator::GetInstance()->GetFloat(randomSize.x, randomSize.y),
			0.0f
		};
		Math::Vector::Vector3 reticlePos = Math::Vector::Add(gun->GetReticlePos(), randomPos);

		Math::Vector::Vector3 prSubtruct = Math::Vector::Subtruct(reticlePos, gun->GetworldTransform().GetWorldPosition());
		Math::Vector::Vector3 Nvelocity = Math::Vector::Normalize(prSubtruct);
		const float speed = 0.5f;
		Math::Vector::Vector3 velocity = Math::Vector::Multiply(Nvelocity, speed);

		shared_ptr<PlayerGunBullet>b = make_shared<PlayerGunBullet>();
		b->Initalize(gun->GetworldTransform().GetWorldPosition(), velocity);
		if (!gun->BulletPushBack(b))
		{
			return;
		}

		bulletRate_ = 0.0f;
		gun->ChangeState(STAND);
	}

}
