#include "Terrain.h"

void Terrain::Initialize()
{
	ModelManager::ModelLoadNormalMap();
	modelHandle_ = ModelManager::LoadObjectFile("Terrain");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create(make_unique<Phong3dPipline>());
	objectDesc_.useLight = true;
	gameObject_->SetDesc(objectDesc_);

	gameObject_->SetModel(modelHandle_);
	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
}

void Terrain::Update()
{
	worldTransform_.UpdateEularMatrix();
}

void Terrain::Draw()
{
	gameObject_->Draw(worldTransform_);
}

void Terrain::ImGuiUpdate()
{
	if (ImGui::TreeNode("Terrain"))
	{
		ImGui::DragFloat3("scale", &worldTransform_.scale.x);
		ImGui::TreePop();
	}
}
