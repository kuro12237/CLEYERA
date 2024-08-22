#include "PlayerStateGoalAnimation.h"

void PlayerStateGoalAnimation::Initialize(Player* p)
{
	auto & goalTransform = GameObjectManager::GetInstance()->GetObj3dData(GoalName_)->GetWorldTransform();
	auto& playerTransform = GameObjectManager::GetInstance()->GetObj3dData(p->GetName())->GetWorldTransform();

	endPos_ = goalTransform.GetWorldPosition();
	startPos_ = playerTransform.GetWorldPosition();
}

void PlayerStateGoalAnimation::Update(Player* p)
{
	auto& playerTransform = GameObjectManager::GetInstance()->GetObj3dData(p->GetName())->GetWorldTransform();

	playerTransform.transform.translate = Math::Vector::SlerpFanc(playerTransform.GetWorldPosition(), endPos_, 0.1f);
	p->GetIsGameEnd() = true;
}
