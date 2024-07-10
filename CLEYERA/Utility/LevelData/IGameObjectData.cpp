#include "IGameObjectData.h"

void IGameObjectData::ImGuiUpdate(string name)
{
	string objname = "object" + name;
	if (ImGui::TreeNode(objname.c_str())) {
		ImGui::DragFloat3("t", &worldTransform_.translate.x);
		ImGui::TreePop();
	}
}
