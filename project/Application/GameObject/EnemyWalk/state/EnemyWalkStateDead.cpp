#include "EnemyWalkStateDead.h"

void EnemyWalkStateDead::Initialize([[maybe_unused]] EnemyWalk* e)
{
	//ブロック以外とは当たらないid
	e->GetCollider()->SetId(ObjectId::kOnlyCollideWithBlocksid);

	gameObjIncetance_ = GameObjectManager::GetInstance();
	auto* emitters = CharacterDeadParticle::GetInstance()->GetEmitter();

	uint32_t index = 0;
	for (auto& emitter : emitters->GetControlParam())
	{
		if (!emitter.useFlag_)
		{
			emitter.useFlag_ = true;
			particleIndex_ = index;
			auto& param = emitters->GetEmitParam()[particleIndex_];
			param.count = 5;
			emitter.frequencyTime = 0.3f;
			param.velocityMax = { 0.1f,0.2f,0.0f };
			param.velocityMin = { -0.1f,0.4f,0.0f };
			param.color = { 0.0f,0.0f,1.0f,1.0f };
			//当たり判定の大きさをもとにemitterを設定
			param.sizeMax = e->GetCollider()->GetAABB().min;
			param.sizeMax = e->GetCollider()->GetAABB().max;
			break;
		}
		index++;
	}
	auto velo = e->GetVelocity();
	velo.y = impactDirection_.y;
	velo.x = e->GetImpactDirection().x;
	e->SetVelocity(velo);
}

void EnemyWalkStateDead::Update([[maybe_unused]] EnemyWalk* e)
{
	auto* emitters = CharacterDeadParticle::GetInstance()->GetEmitter();
	auto& emitterParam = emitters->GetEmitParam()[particleIndex_];
	auto& objData = gameObjIncetance_->GetObj3dDatas()[e->INameable::GetName()];
	auto& desc = gameObjIncetance_->GetObjectDesc(e->INameable::GetName());

	flame_ += flameAdd_;
	//edge設定
	desc.edgeDesc.minmax = { -0.1f,0.2f };
	desc.edgeDesc.mask = flame_;

	if (flame_ >= flameMax_)
	{
		bool& flag = e->GetIsEnd();
		flag = true;
		emitters->Clear(particleIndex_);
	}
	//emitter

	emitterParam.translate = objData->GetWorldTransform().GetWorldPosition();
}
