#include "GameSceneUI.h"

using namespace Engine::Transform;
using namespace Engine::Objects;

void GameSceneUI::Initialize()
{
	//アクション,コントロールクラス初期化
	bottonAction_ = make_unique<GameSceneUIBottonsAction>();
	bottonControl_ = make_unique<GameSceneUIBottonsControl>();

	//joyStickの初期化
	joyStickUis_.resize(joyStickMax_);

	for (size_t i = 0; i < size_t(joyStickMax_); i++)
	{
		joyStickUis_[i].backUi = make_shared<JoyStickBackUI>();
		joyStickUis_[i].stickUi = make_shared<JoyStickUI>();

		sprites_.push_back(joyStickUis_[i].backUi);
		sprites_.push_back(joyStickUis_[i].stickUi);
	}

	string joyStickGropName = "GameSceneJoyStickUI_";
	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_L)].groupName = joyStickGropName;
	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_L)].Initialize(JoyStickLeftRight::Left);

	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_R)].groupName = joyStickGropName;
	joyStickUis_[static_cast<int>(SceneUIEnum::JoyStick_R)].Initialize(JoyStickLeftRight::Right);

	string bottonsGropName = "GameSceneBotton_";
	shared_ptr<BaseBottonUI>bottonA = make_shared<BaseBottonUI>();
	bottonA->Initilaize(bottonsGropName, SceneUIEnum::Botton_A);
	//関数渡す
	bottonA->SetControlActionFunction(std::bind(&GameSceneUIBottonsControl::ControlA, bottonControl_.get()));
	bottonA->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAActive, bottonAction_.get(), std::placeholders::_1));
	bottonA->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonAInactive, bottonAction_.get(), std::placeholders::_1));
	bottonUis_.push_back(move(bottonA));

	shared_ptr<BaseBottonUI>bottonRT = make_shared<BaseBottonUI>();
	bottonRT->Initilaize(bottonsGropName, SceneUIEnum::Botton_RT);
	//関数渡す
	bottonRT->SetControlActionFunction(std::bind(&GameSceneUIBottonsControl::ControlRT, bottonControl_.get()));
	bottonRT->SetIsActionActiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRTActive, bottonAction_.get(), std::placeholders::_1));
	bottonRT->SetIsActionInactiveFunction(std::bind(&GameSceneUIBottonsAction::BottonRTInactive, bottonAction_.get(), std::placeholders::_1));
	bottonUis_.push_back(move(bottonRT));


	string TextGropName = "GameSceneText_";
	for (const string& name : globalVariables_->GetAllDataKey())
	{
		if (globalVariables_->StartsWith(name, TextGropName))
		{
			shared_ptr<BaseBottonUI>ui = make_shared<BaseBottonUI>();
			ui->Initilaize(name, SceneUIEnum::JoyStick_None);
			bottonUis_.push_back(move(ui));
		}
	}


	//uiをpush
	for (weak_ptr<BaseBottonUI>ui : bottonUis_)
	{
		sprites_.push_back(ui.lock());
	}
}

void GameSceneUI::Update()
{
	//ジョイスティック更新
	for (size_t i = 0; i < size_t(joyStickMax_); i++)
	{
		joyStickUis_[i].backUi->Update();
		joyStickUis_[i].stickUi->Update();
	}
	//ボタン更新
	for (weak_ptr<BaseBottonUI> data : bottonUis_)
	{
		auto it = data.lock();
		it->Update();
	}
}

void GameSceneUI::Draw2d()
{
	for (auto& sprite : sprites_)
	{
		auto it = sprite.lock();
		it->Draw2d();
	}
}

void GameSceneUI::ImGuiUpdate()
{
	ImGui::Begin("GameSceneUi");
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

void JoyStickUIData::Initialize(const JoyStickLeftRight& direction)
{
	stickUi->Initilaize(groupName, direction);
	backUi->Initilaize(groupName, direction);
}
