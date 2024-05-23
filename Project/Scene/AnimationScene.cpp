#include "AnimationScene.h"

void AnimationScene::Initialize()
{
	camera_.Initialize();
	camera_.translation_.z = -16;

	worldTransform_.Initialize();
	worldTransform_.translate.y = 8.0f;
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("AnimationScene");
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();

	pointLight_.radious = 32.0f;
	pointLight_.position.y = 4.0f;
	pointLight_.position.z = 8.0f;

	debugModelHandle_ = ModelManager::LoadObjectFile("DebugTestBox");

	//AnimationModel
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create(make_unique<Phong3dSkinningPipline>());

	modelHumanHandle_ = ModelManager::LoadGltfFile(fileName_,true);

	AnimationManager::GetInstance()->LoadAnimation(fileName_);
	animationData_ = AnimationManager::GetInstance()->GetData(fileName_);

	modelHandle_ = modelHumanHandle_;
	gameObject_->SetDesc(gameObjetcDesc);
	gameObject_->SetModel(modelHandle_);
	gameObject_->SetName("walk");
	gameObject_->CreateSkinningParameter();

	debugSkeleton_ = make_unique<DebugSkeleton>();
	debugSkeleton_->Create(gameObject_->GetSkeleton(), worldTransform_);
	testdf_ = make_unique<DefferredShading>();
	testdf_->Initialize();

	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize();
	terrain_ = make_unique<Terrain>();
	terrain_->Initialize();
	CameraManager::GetInstance()->ResetCamera(camera_);
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

	if (ImGui::TreeNode("Light"))
	{
		ImGui::DragFloat3("t", &pointLight_.position.x,-0.1f,0.1f);
		ImGui::DragFloat("intencity", &pointLight_.intencity,-0.1f,0.1f);
		ImGui::DragFloat("radious", &pointLight_.radious, -0.1f, 0.1f);
		ImGui::DragFloat("factor", &pointLight_.decay, -0.1f, 0.1f);
		ImGui::TreePop();
	}
	ImGui::Checkbox("humanObjectDrawFlag", &humanDrawFlag_);
	debugSkeleton_->ImGuiUpdate();

#endif // _USE_IMGUI

	//flame加算
	animationFlame_ += 1.0f / 30.0f;
	animationFlame_ = std::fmod(animationFlame_, animationData_.duration);
	gameObject_->SkeletonUpdate(fileName_, animationFlame_);
	gameObject_->SkinningUpdate();

	worldTransform_.TransfarMatrix();

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);
	skyDome_->Update();
	terrain_->Update();

	LightingManager::AddList(pointLight_);
	postEffect_->Update();
}

void AnimationScene::PostProcessDraw()
{
	testdf_->PreDraw();
	//postEffect_->PreDraw();

	gameObjetcDesc.colorDesc.color_ = { 1,0,1,0.3f };
	if (humanDrawFlag_)
	{
		gameObject_->Draw(worldTransform_);
	}
	debugSkeleton_->Draw(worldTransform_,gameObject_->GetSkeleton());
	terrain_->Draw();
	skyDome_->Draw();
	//postEffect_->PostDraw();
	testdf_->PostDraw();
}

void AnimationScene::Back2dSpriteDraw()
{
}

void AnimationScene::Object3dDraw()
{
	//postEffect_->Draw(camera_);
	testdf_->Draw();
}

void AnimationScene::Flont2dSpriteDraw()
{
}
