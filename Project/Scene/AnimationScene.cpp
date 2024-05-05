#include "AnimationScene.h"

void AnimationScene::Initialize()
{
	camera_.Initialize();
	camera_.translation_.z = -16;
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetDesc(gameObjetcDesc);
	gameObjetcDesc.useLight = true;
	modelHandle_ = ModelManager::LoadGltfFile("simpleSkin");
	AnimationManager::GetInstance()->LoadAnimation("simpleSkin");

	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();

	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("AnimationScene");
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();

	pointLight_.radious = 32.0f;
	pointLight_.position.y = 4.0f;
	pointLight_.position.z = 8.0f;

	debugModelHandle_ = ModelManager::LoadObjectFile("DebugTestBox");
	testBoxWorldTransform_.Initialize();
	testBox_ = make_unique<Game3dObject>();
	testBox_->Create();
	testBoxDesc_.useLight = true;
	testBox_->SetDesc(testBoxDesc_);
	testBox_->SetModel(debugModelHandle_);
}

void AnimationScene::Update(GameManager* Scene)
{
	Scene;
	debugCamera_->ImGuiUpdate();
	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);

	LightingManager::AddList(pointLight_);

	SAnimation::Animation data = AnimationManager::GetInstance()->GetData("simpleSkin");
	animationFlame_ += 1.0f / 60.0f;
	animationFlame_ = std::fmod(animationFlame_, data.duration);

	SAnimation::Skeleton skeleton = ModelManager::GetObjData(modelHandle_).node.skeleton;
	SkinCluster skinCluster = ModelManager::GetObjData(modelHandle_).skinCluster;
	
	AnimationManager::GetInstance()->ApplyAnimation(skeleton, data, animationFlame_);
	ModelManager::SkeletonUpdate(skeleton);

	//ModelManager::SkinClusterUpdate(skinCluster, skeleton);
	ModelManager::SetModel(modelHandle_, skinCluster, skeleton);

	testBoxWorldTransform_.matWorld = ModelManager::GetObjData(modelHandle_).node.children[2].localMatrix;
	//camera_.UpdateMatrix();
	worldTransform_.TransfarMatrix();
	testBoxWorldTransform_.TransfarMatrix();;
	postEffect_->Update();
}

void AnimationScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	gameObject_->Draw(worldTransform_, camera_);
	testBox_->Draw(testBoxWorldTransform_, camera_);
	postEffect_->PostDraw();
}

void AnimationScene::Back2dSpriteDraw()
{
}

void AnimationScene::Object3dDraw()
{
	postEffect_->Draw(camera_);
}

void AnimationScene::Flont2dSpriteDraw()
{
}
