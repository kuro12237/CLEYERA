#include "StageNumber.h"

void StageNumber::Initialize()
{
	INameable::name_ = "StageNumPlane.00" + to_string(number_);
	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	string name = "SelectScene/num" + to_string(number_) + ".png";
	uint32_t texHandle = Engine::Manager::TextureManager::LoadPngTexture(name);

	gameObjectManager_->GetObj3dData(INameable::name_)->GetGameObject()->SetTexHandle(texHandle);
	gameObjectManager_->SetObjectPipline(make_unique<Sprite3dAddNoneWritePiplineCommand>(), INameable::name_);
}

void StageNumber::Update()
{
}
