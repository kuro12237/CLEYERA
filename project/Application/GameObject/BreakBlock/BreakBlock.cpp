#include "BreakBlock.h"

void BreakBlock::Initialize(string name, uint32_t index)
{
	INameable::name_ = name;
	auto& transforms = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform();
	SetObjectData(transforms.transform);
	SetAABB(gameObjectManager_->GetObj3dData(INameable::name_)->GetAABB());

	id_ = kNormalBlock;
	attribute_ = CollisionMask::kBlockAttribute;
	mask_ = CollisionMask::kBlockMask;

	instancingIndex_ = index;
	hp_ = make_unique<BreakBlockHp>();
	const int32_t hpMax = 2;
	hp_->Initialize(hpMax);

	texHandles_.resize(hpMax);
	for (size_t i = 0; i < texHandles_.size(); i++)
	{
		texHandles_[i] = Engine::Manager::TextureManager::LoadPngTexture("BreakBlockTex/BreakBlockTex_"+to_string(i+1)+".png");
	}


}

void BreakBlock::Update()
{
	//hitフラグをクリア
	ClearExtrusion();
	ClearHitDirection();

	

}

void BreakBlock::OnCollision([[maybe_unused]] ICollider* c, [[maybe_unused]] IObjectData* objData)
{
	if (c->GetId() == kPlayerBullet)
	{
		const int32_t subHp = -1;
		hp_->SubtructHp(subHp);

		if (hp_->GetHpCount() != 0)
		{
			uint32_t texhandle = Engine::Manager::TextureManager::LoadPngTexture("BreakBlockTex/BreakBlockTex_1.png");
			gameObjectManager_->GetObj3dData(INameable::name_)->GetGameObject()->SetTexHandle(texhandle);
		}
		if (hp_->GetHpCount() == 0)
		{
			isDead_ = true;
		}
	}
}
