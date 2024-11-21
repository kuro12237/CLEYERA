#include "GameOverUI.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameOverUI::Initialize()
{
	fileName_ = "GameOverSelectUI/uiText_0" + to_string(selectIndex_) + ".png";
	texHandle_ = TextureManager::LoadPngTexture(fileName_);

	this->CreateObject();
	worldTransform_.transform.scale = { scaleMin_,scaleMin_,scaleMin_ };
	ankerPos_ = { 0.5f,0.5f };

	this->CalcAnkerPos();

	texSize_ = TextureManager::GetTextureSize(texHandle_);

}

void GameOverUI::ImGuiUpdate()
{
	string name = fileName_ + "scale";
	ImGui::DragFloat3(name.c_str(), &worldTransform_.transform.scale.x);

}

void GameOverUI::Update()
{
	if (!isSelect_)
	{
		flame_ = 0.0f;
	}
	if (flame_ <= flameMax_ && isSelect_)
	{
		flame_ += 1.0f / 10.0f;
	}

	float scale = Math::Vector::LerpEaseOutSine(scaleMin_, scaleMax_, flame_);
	worldTransform_.transform.scale = { scale,scale,scale };

	worldTransform_.UpdateMatrix();
}
