#include "ClearCoin.h"

void ClearCoin::Initialize(const CoinUse& use)
{
	cameraPos_ = &gameObjectManager_->GetCameraData("Camera")->GetWorldTransform().transform.translate;

	if (use == CoinUse::Active)
	{
		state_ = make_unique<ClearCoinStateActive>();
		state_->Initialize();
	}
}

void ClearCoin::Update()
{

	if (state_)
	{
		state_->Update(this);
	}
}
