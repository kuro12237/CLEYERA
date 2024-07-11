#include "IGameObjectData.h"

void IGameObjectData::ImGuiUpdate(string name)
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::Checkbox("isDraw", &isDraw_);
		ImGui::DragFloat3("scale", &worldTransform_.scale.x, 0.1f);
		ImGui::DragFloat3("rotate", &worldTransform_.rotation.x, 0.1f);
		ImGui::DragFloat3("translate", &worldTransform_.translate.x, 0.1f);
		ImGui::TreePop();
	}
}
