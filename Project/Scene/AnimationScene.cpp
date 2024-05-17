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

	for (int i = 0; i < 128; i++)
	{
		float scale = 0.001f;
		testBoxWorldTransform_[i].Initialize();
		testBoxWorldTransform_[i].scale = { scale,scale ,scale };
		testBox_[i] = make_unique<Game3dObject>();
		testBox_[i]->Create();
		testBox_[i]->SetDesc(testBoxDesc_);
		testBox_[i]->SetModel(debugModelHandle_);
	
		testBox_[i]->SetlectModelPipeline(PHONG_NORMAL_MODEL);
	}

	//AnimationModel
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	
	modelHumanHandle_ = ModelManager::LoadGltfFile(fileName_);
	SModelData modelData = ModelManager::GetObjData(modelHumanHandle_);
	skeleton_ = ModelManager::CreateSkeleton(modelData.node);
	//skelton更新
	ModelManager::SkeletonUpdate(skeleton_);
	//SkinCluster作成
    skinCluster_ = ModelManager::CreateSkinCluster(skeleton_, modelData);
	////skinCluster更新
	ModelManager::SkinClusterUpdate(skinCluster_, skeleton_);

	gameObjetcDesc.skinningAnimationDesc.skinCluster = skinCluster_;
	gameObjetcDesc.useLight = true;


	AnimationManager::GetInstance()->LoadAnimation(fileName_);
	animationData_ = AnimationManager::GetInstance()->GetData(fileName_);

	modelHandle_ = modelHumanHandle_;
	gameObject_->SetDesc(gameObjetcDesc);
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

	debugCamera_->ImGuiUpdate();
#endif // _USE_IMGUI

	//flame加算
	animationFlame_ += 1.0f / 30.0f;
	animationFlame_ = std::fmod(animationFlame_, animationData_.duration);


	//Animation再生
	AnimationManager::ApplyAnimation(skeleton_, animationData_, animationFlame_);
	//スケルトンの更新
	ModelManager::SkeletonUpdate(skeleton_);
	//SkincluserをUpdate
	ModelManager::SkinClusterUpdate(skinCluster_, skeleton_);

	//testModelMat
	array<string, 128 >numberString;;
	for (int i = 0; i < skinCluster_.mappedPalette.size(); ++i) {
		numberString[i] = std::to_string(i);
	}

	for (int i = 0; i < skinCluster_.mappedPalette.size(); i++)
	{
		//testBoxWorldTransform_[i].matWorld = gameObjetcDesc.skinningAnimationDesc.skeleton->joints[i].skeletonSpaceMatrix;

#ifdef _USE_IMGUI
		ImGui::Text("%s :: %f,%f,%f", numberString[i].c_str(), testBoxWorldTransform_[i].GetWorldPosition().x, testBoxWorldTransform_[i].GetWorldPosition().y, testBoxWorldTransform_[i].GetWorldPosition().z);
#endif // _USE_IMGUI

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

	for (int i = 0; i < 65; i++)
	{
		//testBox_[i]->Draw(testBoxWorldTransform_[i], camera_);
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
