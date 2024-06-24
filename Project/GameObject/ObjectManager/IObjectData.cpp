#include "IObjectData.h"

void IObjectData::GetData(GameObjectManager* data)
{
	transform_.scale = data->GetObj3dData(name_).worldTransform.scale;
	transform_.rotate = data->GetObj3dData(name_).worldTransform.rotation;
	transform_.translate = data->GetObj3dData(name_).worldTransform.translate;
	worldMat_ = &data->GetObj3dData(name_).worldTransform.matWorld;

}

void IObjectData::CalcGravity(float g)
{
	velocity_.y += g;
	transform_.translate.y += velocity_.y;
}

