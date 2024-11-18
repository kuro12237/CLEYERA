#include "ClearSceneTitleText.h"

void ClearSceneTitleText::Update(BaseBottonUI& ui)
{
	ui;

	TransformEular transform = ui.GetWorldTransform().transform;

	const float prevScale = 0.25f;
	const float afterScale = 0.35f;


	if (isSelect_)
	{
		if (flame_ <= 1.0f)
		{
			flame_ += 1.0f / 30.0f;
		}
		float scale = Math::Vector::LerpEaseOutSine(prevScale, afterScale, flame_);
		transform.scale = {scale,scale,scale };
		ui.SetTransform(transform);
	}
	else {
		flame_ = 0.0f;
		transform.scale = { prevScale ,prevScale ,prevScale };
		ui.SetTransform(transform);
	}

}
