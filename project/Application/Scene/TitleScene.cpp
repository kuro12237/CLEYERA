#include "TitleScene.h"

void TitleScene::Initialize()
{
	//�Q�[�����ݒ�
	WinApp::GetInstance()->SetTiTleName(L"GunHead");

	//instance��Get
	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();
	gameObjectManager_ = GameObjectManager::GetInstance();
	skyBox_ = SkyBox::GetInstance();

	//��ʑJ�ڏ�����
	changeSceneAnimation_->Initialize();

	//SkyBox�ݒ�
	skyBox_->SetTransform({ {kSkyBoxScale_,kSkyBoxScale_,kSkyBoxScale_},{},{} });
	uint32_t skyBoxTexHandle = TextureManager::LoadDDSTexture("SkyBox/CubeMap.dds");
	skyBox_->SetTexHandle(skyBoxTexHandle);

	//�z�u�f�[�^�ǂݍ���
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(levelDataName_);

	//�I�u�W�F�N�g�Ǘ��N���X�̐ݒ�
	gameObjectManager_->ClearAllData();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset("BackCamera");
	
	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;

}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();

#endif // _USE_IMGUI

	changeSceneAnimation_->Update();

	if (Input::PushBottonPressed(XINPUT_GAMEPAD_B))
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
	}

	gameObjectManager_->Update();

	LightingManager::AddList(light_);

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeState(new SelectScene);
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
	changeSceneAnimation_->Draw();
}
