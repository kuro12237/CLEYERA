#include "ClearCoin.h"

void ClearCoin::Initialize(const CoinUse& use)
{
	cameraPos_ = &gameObjectManager_->GetCameraData("Camera")->GetWorldTransform().transform.translate;
	isUse_ = use;
}

void ClearCoin::Update()
{

	if (state_)
	{
		state_->Update(this);
	}
}

void ClearCoin::ChangeState(unique_ptr<IClearCoinState> state)
{

	state_ = move(state);
	if (state_)
	{
		state_->Initialize();
		state_->Update(this);
	}
}
void ClearCoin::CreateState()
{
	if (isUse_==CoinUse::Active)
	{
		ChangeState(make_unique<ClearCoinStateActive>());
		return;
	}
}
