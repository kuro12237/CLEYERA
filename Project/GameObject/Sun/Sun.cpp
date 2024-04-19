#include "Sun.h"

void Sun::Initialize()
{
	param_.decay = 1.0f;
	param_.position.y = 256.0f;
	param_.position.z = -64.0f;
	param_.radious = 128.0f*3.0f;
	param_.position.z = -16.0f;
}

void Sun::Update()
{
	LightingManager::AddList(param_);
}

void Sun::ImGuiUpdate()
{
	if (ImGui::TreeNode("Sun"))
	{
		ImGui::DragFloat3("translate", &param_.position.x);
		ImGui::DragFloat("radious", &param_.radious);
		ImGui::DragFloat("intensity", &param_.intencity);
		ImGui::TreePop();
	}
}
