#include "Item.h"

void Item::Initialize()
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	uint32_t modelHandle = ModelManager::LoadGltfFile("testItem");
	gameObject_->SetModel(modelHandle);
	gameObjectDesc_.useLight = true;
	gameObject_->SetDesc(gameObjectDesc_);

	worldTransoform_.Initialize();
}

void Item::Update()
{
	worldTransoform_.UpdateMatrix();
}

void Item::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransoform_, camera);
}
