#include "TitleScene.h"

void TitleScene::Initialize()
{
	//ゲーム名設定
	WinApp::GetInstance()->SetTiTleName(L"GunHead");

	//instanceをGet
	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();
	gameObjectManager_ = GameObjectManager::GetInstance();
	skyBox_ = SkyBox::GetInstance();

	//画面遷移初期化
	changeSceneAnimation_->Initialize();

	//配置データ読み込み
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(levelDataName_);

	//オブジェクト管理クラスの設定
	gameObjectManager_->ClearAllData();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset("BackCamera");
	gameObjectManager_->Update();

	camera_ = make_unique<TitleCamera>();
	camera_->Initialize();


	//SkyBox設定
	skyBox_->SetTransform({ {kSkyBoxScale_,kSkyBoxScale_,kSkyBoxScale_},{},{} });
	uint32_t skyBoxTexHandle = TextureManager::LoadDDSTexture("SkyBox/CubeMap.dds");
	skyBox_->SetTexHandle(skyBoxTexHandle);
	//skyBoxとカメラペアレント
	auto& cameraWt = gameObjectManager_->GetCameraData(camera_->GetName())->GetWorldTransform();
	skyBox_->SetParent(cameraWt);
	//カメラのposをポインタでつなぐ
	p_CameraPos_ = &cameraWt.transform.translate;

	arch_ = make_unique<Arch>();
	arch_->Initialize();

	titleLight_ = make_unique<TitleLight>();
	titleLight_->Initialize();

	lava_ = make_unique<Lava>();
	lava_->Initialize();
	lava_->SetCameraParent(cameraWt.transform.translate);

	titleName_ = make_unique<TitleName>();
	titleName_->Initialize();

	//UI
	titlePushA_ = make_unique<TitlePushA>();
	titlePushA_->Initiaize();

	bridge_.resize(bridgeSizeMax_);
	for (size_t i = 0; i < bridgeSizeMax_; i++)
	{
		unique_ptr<Bridge>bridge = make_unique<Bridge>();
		bridge->Initialize();
		if (i != 0)
		{
			string reName = bridge->GetName() + this->FormatNumberWithDots(static_cast<int>(i));
			bridge->SetName(reName);
		}
		bridge_[i] = std::move(bridge);
	}

	towerManager_ = make_unique<TowerManager>();
	towerManager_->Initialize();
	towerManager_->SetP_Camera(cameraWt.transform.translate);

	fireParticle_ = make_unique<FireParticle>();
	fireParticle_->Initialize();

}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	fireParticle_->ImGuiUpdate();

#endif // _USE_IMGUI

	changeSceneAnimation_->Update();

	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		isChangeSelectScene_ = true;
	}

	arch_->Update();
	lava_->Update();
	
	fireParticle_->Emit();
	fireParticle_->Update();
	
	camera_->Update();
	if (camera_->GetIsBridgeAnimationStart() && !isAnimationStart_)
	{
		size_t num = camera_->GetUseBridgeNumber();
		bridge_[num]->SetTargetPos({ 0.0f,0.0f,camera_->GetArchStartOffset() });
		bridge_[num]->SetIsStartAnimation(true);
	}

	for (size_t i = 0; i < bridgeSizeMax_; i++)
	{
		bridge_[i]->Update();
	}

	
	titleLight_->SetPos(*p_CameraPos_);
	titleLight_->Update();

	titleName_->Update();
	titlePushA_->Update();

	towerManager_->Update();

	gameObjectManager_->Update();

	if (isChangeSelectScene_)
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
	}

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeState(new SelectScene);
		return;
	}
}

void TitleScene::PostProcessDraw()
{
	gameObjectManager_->Draw();
	fireParticle_->Draw();

}

void TitleScene::Back2dSpriteDraw()
{
}

void TitleScene::Object3dDraw()
{
}

void TitleScene::Flont2dSpriteDraw()
{
	PostEffect::GetInstance()->Draw();
	changeSceneAnimation_->Draw();
	titlePushA_->Draw();
}

std::string TitleScene::FormatNumberWithDots(int num)
{
	std::ostringstream oss;
	oss << "." << std::setw(3) << std::setfill('0') << num;
	return oss.str();
}
