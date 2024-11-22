#include "StageCoin.h"

void StageCoin::Initilaize()
{
	INameable::name_ = "StageCoin"+FormatNumberWithDots(coinNumber_);
	id_ = IStageCoinId;
	//当たり判定
	//押し出し
	SetObjectData(gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform);
	aabb_ = gameObjectManager_->GetObj3dData(INameable::name_)->GetAABB();
	attribute_ = CollisionMask::kWarpGateAttribute;
	mask_ = CollisionMask::kWarpGateMask;

	gameObjectManager_->GetObj3dData(INameable::name_)->GetDesc().colorDesc.color_ = ColorConverter::ColorConversion(0xf0d64dff);
}

void StageCoin::Update()
{

}

void StageCoin::OnCollision(ICollider* c, IObjectData* objData)
{
	c;
	objData;

	if (c->GetId() == kPlayerId)
	{
		isDead_ = true;
	}
}
