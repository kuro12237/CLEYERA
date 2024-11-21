#include "PlayerStateWarpMove.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateWarpMove::Initialize(Player* p)
{
	railData_ = RailLoader::LoadRail(p->GetWarpFilePath());

	lerpMotion_ = make_unique<LerpMotion>();
	lerpMotion_->SetP_RailData(railData_);
	lerpMotion_->SetIsStartFlag(true);

	p->SetIsUseGravityFlag(false);

	auto& objectData = GameObjectManager::GetInstance()->GetObj3dData(p->INameable::GetName());

	prevModelHandle_ = objectData->GetModelHandle();
	uint32_t modelHandle = ModelManager::LoadObjectFile("PlayerWarp");
	objectData->GetGameObject()->SetModel(modelHandle);
	objectData->GetGameObject()->SetSkinningFlag(false);
	objectData->GetGameObject()->ChangePipline(make_unique<Phong3dPipline>());

	auto& gunObjectData = GameObjectManager::GetInstance()->GetObj3dData("PlayerGun");
	gunObjectData->SetIsDraw(false);
}

void PlayerStateWarpMove::Update(Player* p)
{
	auto& wt = GameObjectManager::GetInstance()->GetObj3dData(p->INameable::GetName())->GetWorldTransform();

	lerpMotion_->UpdateParamerter(kFlame_);
	wt.transform.translate = lerpMotion_->LinearInterpolation();

	if (lerpMotion_->GetIsComplete())
	{
		wt.transform.translate = prevPos_;
		p->SetIsUseGravityFlag(true);

		auto& objectData = GameObjectManager::GetInstance()->GetObj3dData(p->INameable::GetName());
		objectData->GetGameObject()->SetModel(prevModelHandle_);

		objectData->GetGameObject()->ChangePipline(make_unique<Phong3dSkinningPipline>());
		objectData->GetGameObject()->SetSkinningFlag(true);


		auto& gunObjectData = GameObjectManager::GetInstance()->GetObj3dData("PlayerGun");
		gunObjectData->SetIsDraw(true);
		p->MarkStateForRemoval<PlayerStateWarpMove>();
		return;
	}
	prevPos_ = wt.transform.translate;
}
