#include "ISceneUI.h"

void ISceneUI::Draw2d()
{
	for (auto& sprite : sprites_)
	{
		auto it = sprite.lock();

		if (it)
		{
			it->Draw2d();
		}
	}

}

void ISceneUI::ImGuiUpdate()
{
		ImGui::Begin("AddNoneUi");
		static char buffer[256] = "";
		if (ImGui::InputText("SelectLevelDataFilePath", buffer, sizeof(buffer)))
		{
			newSpriteName_ = std::string(buffer);
		}
		string name = "Create_" + newSpriteName_;
		if (ImGui::Button("Create"))
		{
			shared_ptr<BaseBottonUI>ui = make_shared<BaseBottonUI>();
			ui->Initilaize(newSpriteName_, SceneUIEnum::JoyStick_None);
			bottonUis_.push_back(ui);
			sprites_.push_back(ui);
		}

		ImGui::End();
}

void ISceneUI::PushSpriteData()
{
	//ui‚ðpush
	for (weak_ptr<BaseBottonUI>ui : bottonUis_)
	{
		sprites_.push_back(ui.lock());
	}
}

void ISceneUI::KeyCreateEnumNoneUI(const string& gruopKey)
{
	for (const string& name : globalVariables_->GetAllDataKey())
	{
		if (globalVariables_->StartsWith(name, gruopKey))
		{
			shared_ptr<BaseBottonUI>ui = make_shared<BaseBottonUI>();
			ui->Initilaize(name, SceneUIEnum::JoyStick_None);
			bottonUis_.push_back(move(ui));
		}
	}
}