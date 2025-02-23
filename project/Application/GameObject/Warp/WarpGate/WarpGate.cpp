#include "WarpGate.h"

void WarpGate::Initialize()
{
	INameable::name_ = "WarpGate" + FormatNumberWithDots(index_);

	railDataFileName_ = gameObjectManager_->GetObj3dData(INameable::name_)->GetParamFilePaths()[0];

	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetId(ObjectId::kWarpGateId);
	collider_->SetIsExtrusion(true);
	collider_->SetMask(CollisionMask::kWarpGateAttribute);
	collider_->SetAttribute(CollisionMask::kWarpGateMask);

}

void WarpGate::Update()
{
}

void WarpGate::OnCollision([[maybe_unused]] ObjectComponent* objData)
{

}
