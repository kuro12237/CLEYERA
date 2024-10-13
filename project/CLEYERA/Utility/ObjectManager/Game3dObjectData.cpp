#include "Game3dObjectData.h"

void Game3dObjectData::Initialize(TransformEular transform, Game3dObjectDesc desc, uint32_t modelHandle)
{
	modelHandle_ = modelHandle;

	worldTransform_.Initialize();
	worldTransform_.transform = transform;
	gameObject_ = make_unique<Game3dObject>();

	if (ObjectType_ == "MESH")
	{
		gameObject_->Create(make_unique<Phong3dPipline>());
		gameObject_->SetDesc(desc);
		gameObject_->SetModel(modelHandle_);

	}
	if (ObjectType_ == "ARMATURE")
	{
		gameObject_->Create(make_unique<Phong3dSkinningPipline>());
		gameObject_->SetModel(modelHandle_);
		gameObject_->SetName(objectName_);
		gameObject_->SetDesc(desc);

		AnimationManager::GetInstance()->LoadAnimation(modelFilePath_);
		animationData_ = AnimationManager::GetInstance()->GetData(modelFilePath_);

		animationFlame_ += 1.0f / 30.0f;
		animationFlame_ = std::fmod(animationFlame_, animationData_.duration);

		gameObject_->CreateSkinningParameter();
		gameObject_->SkeletonUpdate(modelFilePath_, animationFlame_);
		gameObject_->SkinningUpdate();
	}
}

void Game3dObjectData::WtUpdate(TransformEular transform)
{
	worldTransform_.transform = transform;
	worldTransform_.UpdateMatrix();
	worldTransform_.TransfarMatrix();
}

void Game3dObjectData::SetData(Game3dObjectData* data)
{
	objectName_ = data->objectName_;
	modelHandle_ = data->modelHandle_;
	modelFileName_ = data->modelFileName_;
	gameObject_ = move(data->gameObject_);
	childName_ = data->childName_;
}

void Game3dObjectData::ChangePipline(unique_ptr<IPipelineCommand> piplineSelect)
{
	gameObject_->ChangePipline(move(piplineSelect));
}