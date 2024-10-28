#include "GameOverText.h"

void GameOverText::Initialize()
{
	name_ = "GameOverText";

	auto& wt = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();
	wt.transform.scale = {};

}

void GameOverText::Update()
{

	if (flame_<=flameMax_)
	{
		flame_ += 1.0f/120.0f;
	}

	auto& wt = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();

	float scaleSpeed = Math::Vector::LerpEaseOutSine(0.0f, scaleMax_, flame_);
	wt.transform.scale = { scaleSpeed,scaleSpeed,scaleSpeed };


}
