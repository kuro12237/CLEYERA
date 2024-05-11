#include "AnimationScene.h"

void AnimationScene::Initialize()
{
	camera_.Initialize();
	camera_.translation_.z = -16;

	worldTransform_.Initialize();

	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("AnimationScene");
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();

	pointLight_.radious = 32.0f;
	pointLight_.position.y = 4.0f;
	pointLight_.position.z = 8.0f;

	debugModelHandle_ = ModelManager::LoadObjectFile("DebugTestBox");
	testBoxDesc_.useLight = true;

	for (int i = 0; i < 4; i++)
	{
		testBoxWorldTransform_[i].Initialize();
		testBox_[i] = make_unique<Game3dObject>();
		testBox_[i]->Create();

		testBox_[i]->SetDesc(testBoxDesc_);
		testBox_[i]->SetModel(debugModelHandle_);
		testBox_[i]->SetlectModelPipeline(PHONG_NORMAL_MODEL);
	}
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetDesc(gameObjetcDesc);
	gameObjetcDesc.useLight = true;

	modelHandle_ = ModelManager::LoadGltfFile(fileName_);
	AnimationManager::GetInstance()->LoadAnimation(fileName_);
	animationData_ = AnimationManager::GetInstance()->GetData(fileName_);

	gameObject_->SetModel(modelHandle_);

}

void AnimationScene::Update(GameManager* Scene)
{
#ifdef _USE_IMGUI

	if (ImGui::Button("SceneChange"))
	{
		Scene->ChangeState(new TestScene);
		return;
	}

	if (ImGui::Button("AnimationFlameAdd"))
	{
		animationFlame_ += 1.0f / 60.0f;
	}

	debugCamera_->ImGuiUpdate();
#endif // _USE_IMGUI

	animationFlame_ = std::fmod(animationFlame_, animationData_.duration);

	SAnimation::Skeleton skeleton = ModelManager::GetObjData(modelHandle_).node.skeleton;
	SkinCluster skinCluster = ModelManager::GetObjData(modelHandle_).skinCluster;
	//Animation再生
	//AnimationManager::GetInstance()->ApplyAnimation(skeleton, data, animationFlame_);
	//スケルトンの更新
	ModelManager::SkeletonUpdate(skeleton);
	//SkincluserをUpdate
	ModelManager::SkinClusterUpdate(skinCluster, skeleton);

	ModelManager::SetModel(modelHandle_, skinCluster, skeleton);

	//testModelMat
	array<string, 4>numberString = { "0","1","2","3" };

	for (int i = 0; i < 4; i++)
	{
		testBoxWorldTransform_[i].matWorld = skeleton.joints[i].skeletonSpaceMatrix;
		testBoxWorldTransform_[i].matWorld = skinCluster.mappedPalette[i].skeletonSpaceMatrix;
		//testBoxWorldTransform_[i].matWorld = skinCluster.inverseBindMatrices[i];
		ImGui::Text("%s :: %f,%f,%f", numberString[i].c_str(), testBoxWorldTransform_[i].GetWorldPosition().x, testBoxWorldTransform_[i].GetWorldPosition().y, testBoxWorldTransform_[i].GetWorldPosition().z);
		//testBoxWorldTransform_[i].matWorld = skinCluster.inverseBindMatrices[i];
		testBoxWorldTransform_[i].TransfarMatrix();
	}

	worldTransform_.TransfarMatrix();

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);

	LightingManager::AddList(pointLight_);
	postEffect_->Update();
}

void AnimationScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	gameObject_->Draw(worldTransform_, camera_);
	for (int i = 0; i < 4; i++)
	{
		testBox_[i]->Draw(testBoxWorldTransform_[i], camera_);
	}
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
