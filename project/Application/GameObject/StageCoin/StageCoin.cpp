#include "StageCoin.h"

void StageCoin::Initialize()
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

	gameObjectManager_->GetObj3dData(INameable::name_)->GetDesc().colorDesc.color_ = ColorConverter::ColorConversion(0xf0d64dff);

}

void StageCoin::Update()
{

}

void StageCoin::OnCollision(ObjectComponent* objData)
{
	auto c = objData->GetCollider();
	objData;

	if (c->GetId() == ObjectId::kPlayerId)
	{
		isDead_ = true;
	}
}
