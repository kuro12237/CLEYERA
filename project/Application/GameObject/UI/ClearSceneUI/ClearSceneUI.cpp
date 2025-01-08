#include "ClearSceneUI.h"
using namespace Engine;

void ClearSceneUI::Initialize()
{
	texts_.resize(2);

	for (size_t i = 0; i < 2; i++)
	{
		texts_[i] = make_shared<ClearSceneTitleText>();
		texts_[i]->Initialize("ClearSceneSelectText_" + to_string(i), SceneUIEnum::JoyStick_None);
		this->PushUiMapData(texts_[i]);
	}

	lJoyStick_ = make_unique<ClearSceneJoyStick>();
	shared_ptr<BaseBottonUI>joyStick = make_shared<BaseBottonUI>();
	joyStick->Initialize("ClearSceneJoyStick", SceneUIEnum::JoyStick_L);
	joyStick->SetUpdateFunction(std::bind(&ClearSceneJoyStick::Update, lJoyStick_.get(), std::placeholders::_1));

	this->PushUiMapData(joyStick);

	string bottonBackKey = "UI_";
	clearText_ = make_shared<ClearSceneClearTextUI>();
	clearText_->Initialize("UI_ClearText", SceneUIEnum::JoyStick_None);
	this->PushUiMapData(clearText_);

	string textGroupName = "ClearSceneText_";
	this->KeyCreateEnumNoneUI(textGroupName);

	PushSpriteData();

	uiActiveParticle_ = make_unique<UIActiveParticle>();
	uiActiveParticle_->Initialize();
}

void ClearSceneUI::Update()
{

	//ボタン更新
	this->BottonUiUpdate();

	for (size_t i = 0; i < 2; i++)
	{
		if (i == counter_)
		{
			this->uiActiveParticle_->SetEmitParam(texts_[i]->GetWorldTransform().transform.translate);
			texts_[i]->SetisSelect(true);
		}
		else
		{
			texts_[i]->SetisSelect(false);
		}
	}
	if (!isSelect_)
	{
		if (lJoyStick_->GetIsAction())
		{
			if (Input::GetJoyLStickPos().x >= 0.2f)
			{
				counter_++;
			}
			if (Input::GetJoyLStickPos().x <= -0.2f)
			{
				counter_--;
			}
		}
	}
	if (counter_ < 0)
	{
		counter_ = 1;
	}
	if (counter_ > 1)
	{
		counter_ = 0;
	}

	nextScene_ = static_cast<ClearSceneChangeScene>(counter_);

	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		isSelect_ = true;
	}

	uiActiveParticle_->Update();
}

void ClearSceneUI::ParticleDraw2d()
{
	uiActiveParticle_->Draw();
}
