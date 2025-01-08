#include "TitleSceneUI.h"

void TitleSceneUI::Initialize()
{
	string bottonsGropName = "TitleSceneBotton_";
	shared_ptr<BaseBottonUI>bottonRT = make_shared<BaseBottonUI>();
	bottonRT->Initialize(bottonsGropName, SceneUIEnum::Botton_A);

	this->PushUiMapData(bottonRT);


	string textGroupName = "TitleScene";
	this->KeyCreateEnumNoneUI(textGroupName);

	PushSpriteData();
}

void TitleSceneUI::Update()
{
	this->BottonUiUpdate();
}
