#include "StageCoin.h"

void StageCoin::Initilaize()
{
	INameable::name_ = "StageCoin" + FormatNumberWithDots(coinNumber_);

	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetId(ObjectId::IStageCoinId);
	collider_->SetIsExtrusion(false);
	collider_->SetMask(CollisionMask::kWarpGateMask);
	collider_->SetAttribute(CollisionMask::kWarpGateAttribute);


}

void StageCoin::Update()
{
	ImGui::Begin(INameable::name_.c_str());
	ImGui::DragFloat("metalness", &gameObjectManager_->GetObj3dData(INameable::name_)->GetDesc().pbrDesc.metalness_);
	ImGui::DragFloat("rougmness", &gameObjectManager_->GetObj3dData(INameable::name_)->GetDesc().pbrDesc.roughness_);

	ImGui::End();
}

void StageCoin::OnCollision(IObjectData* objData)
{
	auto c = objData->GetCollider();
	objData;

	if (c->GetId() == ObjectId::kPlayerId)
	{
		isDead_ = true;
	}
}
