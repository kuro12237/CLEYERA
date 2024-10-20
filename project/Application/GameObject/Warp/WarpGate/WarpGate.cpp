#include "WarpGate.h"

void WarpGate::Initialize(const int& index)
{
	name_ = "WarpGate" + FormatNumberWithDots(index);
	railDataFileName_ = gameObjectManager_->GetObj3dData(name_)->GetParamFilePaths()[0];

	//idÝ’è
	id_ = kWarpGateId;

	//“–‚½‚è”»’è
	//‰Ÿ‚µo‚µ
	this->isExtrusion_ = false;
	SetObjectData(gameObjectManager_->GetObj3dData(name_)->GetWorldTransform().transform);
	aabb_ = gameObjectManager_->GetObj3dData(name_)->GetAABB();
	attribute_ = CollisionMask::kWarpGateAttribute;
	mask_ = CollisionMask::kWarpGateMask;
}

void WarpGate::Update()
{
}

void WarpGate::OnCollision([[maybe_unused]]ICollider* c)
{

}
