#include "TitleScene.h"

void TitleScene::Initialize()
{
	camera_.Initialize();
	camera_.UpdateMatrix();
	CameraManager::GetInstance()->ResetCamera(camera_);

	WinApp::GetInstance()->SetTiTleName(L"GunHead");
	PostEffect::GetInstance()->Initialize();
	ChangeSceneAnimation::GetInstance()->Initialize();

	gameObj_ = make_unique<Game3dObject>();
	gameObj_->Create(make_unique<Phong3dPipline>());
	gameObj_->SetModel(ModelManager::LoadObjectFile("DfCube"));
	worldTransform_.Initialize();
	worldTransform_.transform.translate.z = 16.0f;
	
	backTestSprite_ = make_unique<Sprite>();
	backTestSprite_->Initialize();
	backTestSprite_->SetSpriteMode(PerlineNoise);

	backTestSpriteWt_.Initialize();
	uint32_t texHandle = TextureManager::LoadPngTexture("Title/backSprite.png");
	backTestSprite_->SetTexHandle(texHandle);
	backTestSprite_->GetPerlinNoiseScale() = 1.0f;
	backTestSprite_->GetPerlinNoiseFactor() = 1.0f;
}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	ImGui::Begin("TitleScene");
	ImGui::Text("A:PUSH SelectScene");
	ImGui::DragFloat("perlinNOiseS", &backTestSprite_->GetPerlinNoiseScale(), 0.1f);
	ImGui::DragFloat("perlinNOiseF", &backTestSprite_->GetPerlinNoiseFactor(), 0.1f);
	ImGui::DragFloat2("perlinNOiseT", &backTestSprite_->GetPerlinNoisePos().x, 0.1f);
	ImGui::End();

#endif // _USE_IMGUI
	//backTestSprite_->GetPerlinNoisePos().y += 0.01f;

	ChangeSceneAnimation::GetInstance()->Update();

	if (Input::PushBottonPressed(XINPUT_GAMEPAD_B))
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
	}

	backTestSpriteWt_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
	camera_.UpdateMatrix();
	PostEffect::GetInstance()->Update();

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeState(new SelectScene);
		return;
	}
}

void TitleScene::PostProcessDraw()
{
}

void TitleScene::Back2dSpriteDraw()
{
}

void TitleScene::Object3dDraw()
{
	gameObj_->Draw(worldTransform_);
}

void TitleScene::Flont2dSpriteDraw()
{
	backTestSprite_->Draw(backTestSpriteWt_);

	ChangeSceneAnimation::GetInstance()->Draw();

}
