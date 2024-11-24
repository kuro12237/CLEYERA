#include "ClearSceneTitleText.h"

void ClearSceneTitleText::Initialize(const string& groupName, const SceneUIEnum& ui)
{
	this->CreateUIData(groupName, ui);
	SetUpdateFunction(std::bind(&ClearSceneTitleText::UiUpdate,this));
}

void ClearSceneTitleText::UiUpdate()
{
	
	const float prevScale = 0.25f;
	const float afterScale = 0.35f;


	if (isSelect_)
	{
		if (flame_ <= 1.0f)
		{
			flame_ += 1.0f / 30.0f;
		}
		float scale = Math::Vector::LerpEaseOutSine(prevScale, afterScale, flame_);
		worldTransform_.transform.scale = {scale,scale,scale };

	}
	else {
		flame_ = 0.0f;
		worldTransform_.transform.scale = { prevScale ,prevScale ,prevScale };
		
	}

}
