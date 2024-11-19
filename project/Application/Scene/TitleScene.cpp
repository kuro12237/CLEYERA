#include "TitleScene.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;

void TitleScene::Initialize([[maybe_unused]] GameManager* state)
{
	//ゲーム名設定
	WinApp::GetInstance()->SetTiTleName(L"GunHead");

	//グローバル変数のパラメーターファイルの保存先変更
	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/TitleScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/TitleScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/Utility/");
	GlobalVariables::GetInstance()->SetChangeSceneLoadFilesName("Resources/LevelData/ParamData/Utility/");

	//instanceをGet
	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();
	gameObjectManager_ = GameObjectManager::GetInstance();
	skyBox_ = SkyBox::GetInstance();

	//画面遷移初期化
	changeSceneAnimation_->Initialize();

	//配置データ読み込み
	//levelDataの読み込み
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(levelDataName_));

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->MoveData(levelData.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();


	camera_ = make_unique<TitleCamera>();
	camera_->Initialize();

	auto& cameraWt = gameObjectManager_->GetCameraData(camera_->GetName())->GetWorldTransform();
	//カメラのposをポインタでつなぐ
	p_CameraPos_ = &cameraWt.transform.translate;

	//SkyBox設定
	skyBox_->Initialize();
	//skyBoxとカメラペアレント
	skyBox_->SetParent(cameraWt);


	arch_ = make_unique<Arch>();
	arch_->Initialize();

	titleLight_ = make_unique<TitleLight>();
	titleLight_->Initialize();
	titleLight_->SetP_CameraPos(cameraWt.transform.translate);

	lava_ = make_unique<Lava>();
	lava_->Initialize();
	lava_->SetCameraParent(cameraWt.transform.translate);

	titleName_ = make_unique<TitleName>();
	titleName_->Initialize();

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
	
	ui_ = make_unique<TitleSceneUI>();
	ui_->Initialize();

	stageManager_ = StageManager::GetInstance();

	stageManager_->Initilaize();

	this->SetFlont2dSpriteDrawFunc(std::bind(&TitleScene::Flont2dSpriteDraw, this));
	this->SetPostEffectDrawFunc(std::bind(&TitleScene::PostProcessDraw, this));


}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	//fireEmberParticle_->ImGuiUpdate();

	changeSceneAnimation_->ImGuiUpdate();
	ui_->ImGuiUpdate();
	
#endif // _USE_IMGUI


	changeSceneAnimation_->Update();

	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		isChangeSelectScene_ = true;
	}

	arch_->Update();
	lava_->Update();


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


	titleLight_->Update();

	titleName_->Update();

	towerManager_->Update();

	gameObjectManager_->Update();

	ui_->Update();


	if (isChangeSelectScene_)
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
	}

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeScene(make_unique<SelectScene>());
		return;
	}
}

void TitleScene::PostProcessDraw()
{
	gameObjectManager_->Draw();
}

void TitleScene::Flont2dSpriteDraw()
{
	//fireEmberParticle_->Draw();
	ui_->Draw2d();

	changeSceneAnimation_->Draw();

}

std::string TitleScene::FormatNumberWithDots(int num)
{
	std::ostringstream oss;
	oss << "." << std::setw(3) << std::setfill('0') << num;
	return oss.str();
}
