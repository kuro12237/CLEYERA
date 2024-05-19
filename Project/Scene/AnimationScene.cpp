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

		ImGui::DragFloat("factor", &pointLight_.decay, -0.1f, 0.1f);
		ImGui::TreePop();
	}

#endif // _USE_IMGUI

	//flame加算
	animationFlame_ += 1.0f / 30.0f;
	animationFlame_ = std::fmod(animationFlame_, animationData_.duration);
	gameObject_->SkeletonUpdate(fileName_, animationFlame_);
	gameObject_->SkinningUpdate();

	worldTransform_.TransfarMatrix();

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);

	LightingManager::AddList(pointLight_);
	postEffect_->Update();
}

void AnimationScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	//gameObject_->Draw(worldTransform_, camera_);
	debugSkeleton_->Draw(camera_,gameObject_->GetSkeleton());
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
