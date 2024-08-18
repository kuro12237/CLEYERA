#include "EnemyWalkStateDead.h"

void EnemyWalkStateDead::Initialize([[maybe_unused]] EnemyWalk* e)
{
	//ブロック以外とは当たらないid
	e->SetId(kOnlyCollideWithBlocksid);

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
			param.velocityMax = { 0.01f,0.05f,0.0f };
			param.velocityMin = { -0.01f,0.1f,0.0f };
			break;
		}
		index++;
	}
}

void EnemyWalkStateDead::Update([[maybe_unused]] EnemyWalk* e)
{
	auto* emitters = CharacterDeadParticle::GetInstance()->GetEmitter();
	auto& emitterParam = emitters->GetEmitParam()[particleIndex_];
	auto& objData = gameObjIncetance_->GetObj3dDatas()[e->GetName()];
	auto& desc = gameObjIncetance_->GetObjectDesc(e->GetName());

	//edge設定
	desc.edgeDesc.minmax = { -0.1f,0.2f };
	desc.edgeDesc.mask += 1.0f / 60.0f;
	desc.edgeDesc.edgeColor = { 0.0f,0.0f,1.0f,0.0f };
	flame_ += 1.0f / 60.0f;
	if (flame_ >= flameMax_)
	{
		bool& flag = e->GetIsEnd();
		flag = true;
		emitters->Clear(particleIndex_);
	}
	//emitter
	emitterParam.translate = objData->GetWorldTransform().GetWorldPosition();
}
