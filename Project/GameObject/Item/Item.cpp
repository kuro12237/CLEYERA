#include "Item.h"

void Item::Initialize()
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	uint32_t modelHandle = ModelManager::LoadGltfFile("testItem");
	gameObject_->SetModel(modelHandle);
	gameObjectDesc_.useLight = true;
	gameObject_->SetDesc(gameObjectDesc_);

	animationHandle_ = AnimationManager::GetInstance()->LoadAnimation("testItem");

	worldTransform_.Initialize();
}

void Item::Update()
{
	SAnimation::Animation data = AnimationManager::GetInstance()->GetData("testItem");
	animationTimer_ += 1.0f / 60.0f;
	animationTimer_ = std::fmod(animationTimer_, data.duration);
	SAnimation::NodeAnimation& rootNodeAnimation = data.NodeAnimation["testItem"];
	Math::Vector::Vector3 translate = AnimationManager::CalculateValue(rootNodeAnimation.translate.keyframes, animationTimer_);
	Math::Qua::Quaternion quaternion = AnimationManager::CalculateValue(rootNodeAnimation.rotate.keyframes, animationTimer_);
	Math::Vector::Vector3 scale = AnimationManager::CalculateValue(rootNodeAnimation.scale.keyframes, animationTimer_);

	Math::Matrix::Matrix4x4 tm = Math::Matrix::TranslateMatrix(translate);
	Math::Matrix::Matrix4x4 rm = Math::Qua::RotateMatrix(quaternion);
	Math::Matrix::Matrix4x4 sm = Math::Matrix::ScaleMatrix(scale);
	Math::Matrix::Matrix4x4 localMat = Math::Matrix::Multiply(sm, Math::Matrix::Multiply(rm, tm));
	worldTransform_.matWorld = Math::Matrix::Multiply(worldTransform_.matWorld, localMat);
	worldTransform_.TransfarMatrix();

	//worldTransoform_.UpdateMatrix();
}

void Item::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_, camera);
}
