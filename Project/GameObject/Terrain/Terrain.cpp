#include "Terrain.h"

void Terrain::Initialize()
{
	modelHandle_ = ModelManager::LoadObjectFile("Terrain");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);
	objectDesc_.useLight = true;
	gameObject_->SetDesc(objectDesc_);

	worldTransform_.Initialize();
	worldTransform_.scale = { 8.0f,8.0f,8.0f };
}

void Terrain::Update()
{
	worldTransform_.UpdateEularMatrix();
}

void Terrain::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_, camera);
}

void Terrain::ImGuiUpdate()
{
	if (ImGui::TreeNode("Terrain"))
	{
		ImGui::DragFloat3("scale", &worldTransform_.scale.x);
		ImGui::TreePop();
	}
}
