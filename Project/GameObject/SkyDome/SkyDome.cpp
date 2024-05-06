#include "SkyDome.h"

void SkyDome::Initialize()
{
	modelHandle_ = ModelManager::LoadObjectFile("SkyDome");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);
	gameObjectDesc_.useLight = true;
	gameObject_->SetDesc(gameObjectDesc_);
	gameObject_->SetlectModelPipeline(PHONG_NORMAL_MODEL);
	worldTransform_.Initialize();
	worldTransform_.scale = { 128.0f,128.0f,128.0f };
}

void SkyDome::Update()
{
	worldTransform_.UpdateEularMatrix();
}

void SkyDome::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_, camera);
}

void SkyDome::ImGuiUpdate()
{
	if (ImGui::TreeNode("SkyDome"))
	{
		ImGui::DragFloat3("Scale", &worldTransform_.scale.x);
		ImGui::TreePop();
	}
}
