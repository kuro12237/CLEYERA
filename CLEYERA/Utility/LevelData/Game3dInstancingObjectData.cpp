#include "Game3dInstancingObjectData.h"

void Game3dInstancingObjectData::Initialize(string objectGropName, uint32_t modelHandle)
{
	objectType_ = objectGropName;
	gameInstancingObject_ = make_unique<GameInstancing3dObject>();
	gameInstancingObject_->Create(128,objectGropName);
	modelHandle_ = modelHandle;

	gameInstancingObject_->SetModel(modelHandle_);
}
