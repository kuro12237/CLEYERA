#include "IObjectData.h"

void IObjectData::Create()
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create(make_unique<Phong3dPipline>());
	//worldTransform_.Initialize(); 
}

void IObjectData::MoveData(Game3dObjectData &data)
{
	gameObject_->SetModel(data.modelHandle);
	gameObject_->SetDesc(data.objectDesc);
	worldTransform_ = move(data.worldTransform);
}

