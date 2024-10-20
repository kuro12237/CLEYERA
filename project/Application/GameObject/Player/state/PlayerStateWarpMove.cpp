#include "PlayerStateWarpMove.h"

void PlayerStateWarpMove::Initialize(Player* p)
{
	railData_ = RailLoader::LoadRail(p->GetWarpFilePath());
	splineMotion_ = make_unique<SplineMotion>();
	splineMotion_->SetP_RailData(railData_);
	splineMotion_->SetIsStartFlag(true);
	p->SetIsUseGravityFlag(false);
}

void PlayerStateWarpMove::Update(Player* p)
{
	auto& wt = GameObjectManager::GetInstance()->GetObj3dData(p->GetName())->GetWorldTransform();

	splineMotion_->UpdateParamerter(kFlame_);
	wt.transform.translate = splineMotion_->CatmullRomInterpolation();

	if (splineMotion_->GetIsComplete())
	{
		p->SetIsUseGravityFlag(true);
		p->ChangeState(make_unique<PlayerStateNone>());
	}

}
