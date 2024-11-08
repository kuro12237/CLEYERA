#include "TitleSceneUI.h"

void TitleSceneUI::Initialize()
{
	string bottonsGropName = "TitleSceneBotton_";
	shared_ptr<BaseBottonUI>bottonRT = make_shared<BaseBottonUI>();
	bottonRT->Initilaize(bottonsGropName, SceneUIEnum::Botton_A);
	bottonUis_.push_back(move(bottonRT));

	PushSpriteData();
}

void TitleSceneUI::Update()
{
	//ボタン更新
	for (weak_ptr<BaseBottonUI> data : bottonUis_)
	{
		auto it = data.lock();
		it->Update();
	}
}
