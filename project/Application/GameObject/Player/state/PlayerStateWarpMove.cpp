#include "PlayerStateWarpMove.h"

void PlayerStateWarpMove::Initialize(Player* p)
{
	railData_ = RailLoader::LoadRail(p->GetWarpFilePath());

	lerpMotion_ = make_unique<LerpMotion>();
	lerpMotion_->SetP_RailData(railData_);
	lerpMotion_->SetIsStartFlag(true);

	p->SetIsUseGravityFlag(false);

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
		p->ChangeState(make_unique<PlayerStateNone>());
		return;
	}
	prevPos_ = wt.transform.translate;
}
