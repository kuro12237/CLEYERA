#include "StageCoin.h"

void StageCoin::Initilaize()
{
	INameable::name_ = "StageCoin"+FormatNumberWithDots(coinNumber_);
	id_ = IStageCoinId;
	//“–‚½‚è”»’è
	//‰Ÿ‚µo‚µ
	SetObjectData(gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform);
	aabb_ = gameObjectManager_->GetObj3dData(INameable::name_)->GetAABB();
	attribute_ = CollisionMask::kWarpGateAttribute;
	mask_ = CollisionMask::kWarpGateMask;

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
