#include "Game3dInstancingObjectData.h"

void Game3dInstancingObjectData::Initialize(string objectGropName, uint32_t modelHandle)
{
	objectType_ = objectGropName;
	gameInstancingObject_ = make_unique<GameInstancing3dObject>();
	gameInstancingObject_->Create(instanceMax_,objectGropName);
	modelHandle_ = modelHandle;

	gameInstancingObject_->SetModel(modelHandle_);
}

void Game3dInstancingObjectData::ImGuiUpdate()
{
	for (uint32_t i = 0; i < transform_.size(); i++)
	{
		auto& transform = transform_[i]->GetTransform();
		string name = "Transform" + to_string(i);
		if (ImGui::TreeNode(name.c_str()))
		{
			ImGui::DragFloat3("scale", &transform.scale.x, 0.1f);
			ImGui::DragFloat3("rotate", &transform.rotate.x, 0.1f);
			ImGui::DragFloat3("translate", &transform.translate.x, 0.1f);
			ImGui::TreePop();
		}
	}

}

void Game3dInstancingObjectData::PushObjectData(uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		gameInstancingObject_->PushVector(transform_[i], size);
	}
}
