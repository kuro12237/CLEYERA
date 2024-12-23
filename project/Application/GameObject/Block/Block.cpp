#include "Block.h"

void Block::Initialize(string name, uint32_t index)
{
	INameable::name_ = name + to_string(index);
	auto& transforms = gameObjectManager_->GetObjInstancingData(name)->GetTransforms()[index];

	//dataをセット
	//objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	//this->SetColliderParamData();
	collider_->SetOnCollisionFunc(std::bind(&IObjectData::OnCollision, this, std::placeholders::_1));

	collider_->SetObjectData(transforms->GetTransform());
	collider_->SetAABB(transforms->GetAABB());
	collider_->SetId(ObjectId::kNormalBlock);
	collider_->SetMask(CollisionMask::kBlockMask);
	collider_->SetAttribute(CollisionMask::kBlockAttribute);

}

void Block::Update()
{
	//hitフラグをクリア
	collider_->ClearExtrusion();
	collider_->ClearHitDirection();
}

void Block::OnCollision([[maybe_unused]]IObjectData* objData)
{
	//c;
}
