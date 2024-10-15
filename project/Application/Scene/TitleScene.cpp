#include "TitleScene.h"

void TitleScene::Initialize()
{
	//�Q�[�����ݒ�
	WinApp::GetInstance()->SetTiTleName(L"GunHead");
	//�O���[�o���ϐ��̃p�����[�^�[�t�@�C���̕ۑ���ύX
	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/");
	GlobalVariables::GetInstance()->LoadFiles();

	//instance��Get
	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();
	gameObjectManager_ = GameObjectManager::GetInstance();
	skyBox_ = SkyBox::GetInstance();

	//��ʑJ�ڏ�����
	changeSceneAnimation_->Initialize();

	//�z�u�f�[�^�ǂݍ���
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(levelDataName_);

	//�I�u�W�F�N�g�Ǘ��N���X�̐ݒ�
	gameObjectManager_->ClearAllData();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset("BackCamera");
	gameObjectManager_->Update();

	camera_ = make_unique<TitleCamera>();
	camera_->Initialize();

	auto& cameraWt = gameObjectManager_->GetCameraData(camera_->GetName())->GetWorldTransform();
	//�J������pos���|�C���^�łȂ�
	p_CameraPos_ = &cameraWt.transform.translate;

	//SkyBox�ݒ�
	skyBox_->Initialize();
	//skyBox�ƃJ�����y�A�����g
	skyBox_->SetParent(cameraWt);


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


	//fireEmberParticle_ = make_unique<FireEmber2dParticle>();
	//fireEmberParticle_->Initialize();
}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	//fireEmberParticle_->ImGuiUpdate();

	changeSceneAnimation_->ImGuiUpdate();


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
		Scene->ChangeScene(make_unique<SelectScene>());
		return;
	}
}

void TitleScene::PostProcessDraw()
{
	gameObjectManager_->Draw();
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

	titlePushA_->Draw();
	//fireEmberParticle_->Draw();

	changeSceneAnimation_->Draw();

}

std::string TitleScene::FormatNumberWithDots(int num)
{
	std::ostringstream oss;
	oss << "." << std::setw(3) << std::setfill('0') << num;
	return oss.str();
}
