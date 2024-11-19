#include "ISceneUI.h"

void ISceneUI::Draw2d()
{
	for (auto& sprite : sprites_)
	{
		auto it = sprite.second;
		auto sp = it.lock();

		if (!sp)
		{
			continue;
		}
		if (!sp->GetTexHandle() == 0)
		{
			sp->Draw2d();
		}

	}

}

void ISceneUI::ImGuiUpdate()
{
#ifdef _USE_IMGUI

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

		sprites_[ui->GetName()] = ui;
	}

	ImGui::End();
#endif // _USE_IMGUI

}

void ISceneUI::PushSpriteData()
{
	//ui‚ðpush
	for (weak_ptr<BaseBottonUI>ui : bottonUis_)
	{
		auto button = ui.lock();
		if (sprites_.find(button->GetName()) == sprites_.end()) {
			sprites_[button->GetName()] = button;
		}
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