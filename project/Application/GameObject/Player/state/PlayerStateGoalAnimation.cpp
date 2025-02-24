#include "PlayerStateGoalAnimation.h"

void PlayerStateGoalAnimation::Initialize(Player* p)
{
	auto& goalTransform = GameObjectManager::GetInstance()->GetObj3dData(p->GetHitGoalName())->GetWorldTransform();
	auto& playerTransform = GameObjectManager::GetInstance()->GetObj3dData(p->INameable::GetName())->GetWorldTransform();

	endPos_ = goalTransform.GetWorldPosition();
	startPos_ = playerTransform.GetWorldPosition();
        p->SetIsUseGravityFlag(false);
}

void PlayerStateGoalAnimation::Update(Player* p)
{
	auto& playerTransform = GameObjectManager::GetInstance()->GetObj3dData(p->INameable::GetName())->GetWorldTransform();
	auto& playerGunTransform = GameObjectManager::GetInstance()->GetObj3dData(PlayerGunName_)->GetWorldTransform();

	if (playerTransform.transform.scale.x <= 0.0f)
	{
		playerTransform.transform.translate = endPos_;
		p->GetIsGameEnd() = true;
	}
	else
	{
		float kPlayerScale = 0.01f;
		float kGunScale = 0.02f;
		playerTransform.transform.scale = Math::Vector::Add(playerTransform.transform.scale, { -kPlayerScale , -kPlayerScale , -kPlayerScale });
		playerTransform.transform.translate = Math::Vector::Lerp(playerTransform.GetWorldPosition(), endPos_, 0.5f);
		playerTransform.transform.rotate.z += float(numbers::pi / 30.0f);
		playerGunTransform.transform.scale = Math::Vector::Add(playerGunTransform.transform.scale, { -kGunScale , -kGunScale , -kGunScale });
		playerGunTransform.transform.translate = Math::Vector::Lerp(playerGunTransform.GetWorldPosition(), endPos_, 0.1f);
		playerGunTransform.transform.rotate.z += float(numbers::pi / 30.0f);
	}
	
}
