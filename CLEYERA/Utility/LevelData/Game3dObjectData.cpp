#include "Game3dObjectData.h"

void Game3dObjectData::Initialize(TransformEular transform, Game3dObjectDesc desc, uint32_t modelHandle)
{
	objectDesc_ = desc;
	modelHandle_ = modelHandle;

	worldTransform_.Initialize();
	worldTransform_.translate = transform.translate;
	worldTransform_.scale = transform.scale;
	worldTransform_.rotation = transform.rotate;

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->SetDesc(objectDesc_);
	gameObject_->Create(make_unique<Phong3dPipline>());
	gameObject_->SetModel(modelHandle_);

}

void Game3dObjectData::WtUpdate(TransformEular transform)
{
	worldTransform_.scale = transform.scale;
	worldTransform_.rotation = transform.rotate;
	worldTransform_.translate = transform.translate;
	worldTransform_.UpdateMatrix();
	worldTransform_.TransfarMatrix();
}

void Game3dObjectData::SetData(Game3dObjectData* data)
{
	objectName_ = data->objectName_;
	modelHandle_ = data->modelHandle_;
	modelFileName_ = data->modelFileName_;
	gameObject_ = move(data->gameObject_);
	objectDesc_ = data->objectDesc_;
	childName_ = data->childName_;
}