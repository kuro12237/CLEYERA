#include "ClearSceneClearTextUi.h"


void ClearSceneClearTextUI::Initialize(const string& groupName, const SceneUIEnum& ui)
{
	this->CreateUIData(groupName, ui);

	this->SetUpdateFunction(std::bind(&ClearSceneClearTextUI::UiUpdate, this));

	sprite_->SetColor({ 1.0f,1.0f,1.0f,0.0f });
}

void ClearSceneClearTextUI::UiUpdate()
{
	if (isStart_)
	{
		if (flame_ <= flameMax_)
		{
			flame_ += 1.0f / 60.0f;
			float scale = Math::Vector::LerpEaseOutSine(5.0f, 0.5f, flame_);
			float alpha = Math::Vector::LerpEaseOutSine(-1.0f, 1.0f, flame_);

			worldTransform_.transform.scale = { scale,scale,scale };
			sprite_->SetColor({ 1.0f,1.0f,1.0f,alpha });
		}
	}
	else
	{
		this->worldTransform_.transform.scale = { 5.0f,5.0f,5.0f };
	}
}
