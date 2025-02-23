#include "BreakBlock.h"

void BreakBlock::Initialize()
{

	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetId(ObjectId::kNormalBlock);
	collider_->SetIsExtrusion(false);
	collider_->SetMask(CollisionMask::kBlockAttribute);
	collider_->SetAttribute(CollisionMask::kBlockMask);


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

void BreakBlock::OnCollision([[maybe_unused]] ObjectComponent* objData)
{
	auto c = objData->GetCollider();
	if (c->GetId() == ObjectId::kPlayerBullet)
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
