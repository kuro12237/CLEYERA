#include "ClearSceneUI.h"

void ClearSceneUI::Initialize()
{


	texts_.resize(2);

	for (size_t i = 0; i < 2; i++)
	{
		texts_[i] = make_unique<ClearSceneTitleText>();

		shared_ptr<BaseBottonUI>botton = make_shared<BaseBottonUI>();
		botton->Initilaize("ClearSceneSelectText_"+to_string(i), SceneUIEnum::JoyStick_None);
		botton->SetUpdateFunction(std::bind(&ClearSceneTitleText::Update, texts_[i].get(), std::placeholders::_1));

		bottonUis_.push_back(move(botton));
		sprites_.push_back(bottonUis_[i]);
	}

	lJoyStick_ = make_unique<ClearSceneJoyStick>();
	shared_ptr<BaseBottonUI>joyStick = make_shared<BaseBottonUI>();
	joyStick->Initilaize("ClearSceneJoyStick", SceneUIEnum::JoyStick_L, std::bind(&ClearSceneJoyStick::Initialize, lJoyStick_.get(), std::placeholders::_1));
	joyStick->SetUpdateFunction(std::bind(&ClearSceneJoyStick::Update, lJoyStick_.get(), std::placeholders::_1));

	bottonUis_.push_back(move(joyStick));

	//PushSpriteData();
	


}

void ClearSceneUI::Update()
{
	//ボタン更新
	for (weak_ptr<BaseBottonUI> data : bottonUis_)
	{
		auto it = data.lock();
		it->Update();
	}

	for (size_t i = 0; i < 2; i++)
	{
		if (i == counter_)
		{
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

}
