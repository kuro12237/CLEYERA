#include "Block.h"

void Block::Initialize(string name, uint32_t index)
{
	INameable::name_ = name + to_string(index);
	auto& transforms = gameObjectManager_->GetObjInstancingData(name)->GetTransforms()[index];

	//dataをセット
	collider_->SetOnCollisionFunc(std::bind(&IObjectData::OnCollision, this, std::placeholders::_1));

	collider_->SetObjectData(transforms->GetTransform());
	collider_->SetAABB(transforms->GetAABB());
	collider_->SetId(ObjectId::kNormalBlock);
	collider_->SetMask(CollisionMask::kBlockMask);
	collider_->SetAttribute(CollisionMask::kBlockAttribute);

	boxField_->GetParam(index).use = 1;
	boxField_->GetParam(index).translate = transforms->GetTransform().translate;
	boxField_->GetParam(index).sizeMax = transforms->GetTransform().scale;
	boxField_->GetParam(index).sizeMin = Math::Vector::Multiply(transforms->GetTransform().scale,-1.0f);
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
