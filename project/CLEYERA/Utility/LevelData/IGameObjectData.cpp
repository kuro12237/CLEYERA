#include "IGameObjectData.h"

void IGameObjectData::ImGuiUpdate(string name)
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::Checkbox("isDraw", &isDraw_);
		ImGui::DragFloat3("scale", &worldTransform_.transform.scale.x, 0.1f);
		ImGui::DragFloat3("rotate", &worldTransform_.transform.rotate.x, 0.1f);
		ImGui::DragFloat3("translate", &worldTransform_.transform.translate.x, 0.1f);
		ImGui::Separator();
		ImGui::TreePop();
	}
}


