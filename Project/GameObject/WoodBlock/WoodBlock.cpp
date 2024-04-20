#include "WoodBlock.h"

void WoodBlock::Initialize(const TransformQua &t)
{
	worldMat_ = Math::Matrix::Identity();
	translate_ = t.translate;
	scale_ = t.scale;
	translate_.y += 0.5f;
	aabb_.min = { -0.5f,-0.5f,-0.5f };
	aabb_.max = { 0.5f,0.5f,0.5f };

	SetMatWorld(worldMat_);
	SetAABB(aabb_);
	SetAttbute(kWoodBlockAttbute);
	SetMask(kWoodBlockMask);
	IBoxCollider::SetId(kWoodBlockId);

	SetVelocity(velocity_);
}

void WoodBlock::Update()
{
	isHit_ = false;
	//translate_.y += 0.1f;
	worldMat_ = Math::Matrix::AffineMatrix(scale_, rotate_, translate_);
}



Math::Vector::Vector3 WoodBlock::GetWorldPosition()
{
	return Math::Vector::Vector3(worldMat_.m[3][0], worldMat_.m[3][1], worldMat_.m[3][2]);
}

void WoodBlock::OnCollision(IBoxCollider* collider)
{
	collider;
	isHit_ = true;
}

void WoodBlock::SetTransformQua(const TransformQua& q)
{
	scale_ = q.scale;
	translate_ = q.translate;
}

void WoodBlock::UpdateImGui()
{
	if (isHit_)
	{
		ImGui::Text("Hit:BlockNumber %d",blockNamber_);
	}
}
