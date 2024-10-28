#include "GameOverUI.h"

void GameOverUI::Initialize()
{
	fileName_ = "GameOverSelectUI/uiText_0"+to_string(selectIndex_)+".png";
	texHandle_ = TextureManager::LoadPngTexture(fileName_);

	this->CreateObject();
	worldTransform_.transform.scale = scale_;
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
	worldTransform_.UpdateMatrix();
}
