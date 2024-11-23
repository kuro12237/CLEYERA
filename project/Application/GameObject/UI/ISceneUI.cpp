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
		ui->Initialize(newSpriteName_, SceneUIEnum::JoyStick_None);
		bottonUis_[ui->GetName()] = ui;
		sprites_[ui->GetName()] = ui;
	}

	ImGui::End();
#endif // _USE_IMGUI

}

void ISceneUI::PushSpriteData()
{
	//uiをpush
	for (auto & ui : bottonUis_)
	{
	  weak_ptr<BaseBottonUI> it = ui.second;
	  auto button = it.lock();
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
			ui->Initialize(name, SceneUIEnum::JoyStick_None);
			bottonUis_[name] = (move(ui));
		}
	}
}

void ISceneUI::PushUiMapData(shared_ptr<BaseBottonUI>ui)
{
	bottonUis_[ui->GetName()] = ui;
}

void ISceneUI::BottonUiUpdate()
{
	//ボタン更新
	for (auto& data : bottonUis_)
	{
		weak_ptr<BaseBottonUI> it = data.second;
		auto ui = it.lock();
		ui->Update();
	}
}
