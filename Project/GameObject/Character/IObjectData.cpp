#include "IObjectData.h"

void IObjectData::GameObjectCreate(const string filePath, const Game3dObjectDesc& desc)
{
	desc_ = desc;
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->SetDesc(desc);
	gameObject_->SetModel(filePath);
	gameObject_->Create(make_unique<Phong3dPipline>());
}

void IObjectData::WtCreate(const TransformEular& transform, const WorldTransform* wt)
{
	worldTransform_.Initialize();
	worldTransform_.scale = transform.scale;
	worldTransform_.rotation = transform.rotate;
	worldTransform_.translate = transform.translate;
	//parent
	if (wt)
	{
		worldTransform_.parent = wt;
	}
	worldTransform_.UpdateMatrix();

}

void IObjectData::UpdateMat()
{
	worldTransform_.UpdateMatrix();
}

void IObjectData::DrawObject(CameraData camera)
{
	gameObject_->Draw(worldTransform_, camera);
}
