#include "Block.h"

void Block::Initialize()
{

	auto& transforms = gameObjectManager_->GetObjInstancingData(name_)->GetTransforms()[blockNumber_];

	//dataをセット
	collider_->SetOnCollisionFunc(std::bind(&ObjectComponent::OnCollision, this, std::placeholders::_1));

	collider_->SetObjectData(transforms->GetTransform());
	collider_->SetAABB(transforms->GetAABB());
	collider_->SetId(ObjectId::kNormalBlock);
	collider_->SetMask(CollisionMask::kBlockMask);
	collider_->SetAttribute(CollisionMask::kBlockAttribute);

	boxField_->GetParam(blockNumber_).use = 1;
	boxField_->GetParam(blockNumber_).translate = transforms->GetTransform().translate;
	boxField_->GetParam(blockNumber_).sizeMax = transforms->GetTransform().scale;
	boxField_->GetParam(blockNumber_).sizeMin = Math::Vector::Multiply(transforms->GetTransform().scale,-1.0f);
}

void Block::Update()
{
	//hitフラグをクリア
	collider_->ClearExtrusion();
	collider_->ClearHitDirection();
}

void Block::OnCollision([[maybe_unused]]ObjectComponent* objData)
{
	//c;
}
