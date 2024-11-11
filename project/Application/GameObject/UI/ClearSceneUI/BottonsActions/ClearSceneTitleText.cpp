#include "ClearSceneTitleText.h"

void ClearSceneTitleText::Update(BaseBottonUI& ui)
{
	ui;

	TransformEular transform = ui.GetWorldTransform().transform;

	if (isSelect_)
	{
		
		transform.scale = { 0.35f,0.35f,0.35f };
		ui.SetTransform(transform);
	}
	else {
		transform.scale = { 0.25f,0.25f,0.25f };
		ui.SetTransform(transform);
	}

}
