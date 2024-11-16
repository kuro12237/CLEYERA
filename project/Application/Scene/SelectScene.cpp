#include "SelectScene.h"

using namespace Engine::Manager;


void SelectScene::Initialize()
{
	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/SelectScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/SelectScene/");

	//levelData�̓ǂݍ���
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->MoveData(levelData.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();


	characterDeadParticle_ = CharacterDeadParticle::GetInstance();
	characterDeadParticle_->Initialize();

	characterMoveParticle_ = CharacterMoveParticle::GetInstance();
	characterMoveParticle_->Initialize();

	GoalParticle::GetInstance()->Initialize();
	GoalParticle::GetInstance()->Clear();
	player_ = make_unique<PlayerManager>();
	player_->Initialize();

	goals_.resize(portalMax_);

	for (size_t portalIndex = 0; portalIndex < portalMax_; portalIndex++)
	{
		shared_ptr<Goal>goal = make_shared<Goal>();

		goals_[portalIndex] = make_shared<Goal>();
		goals_[portalIndex]->Initialize(kPortalIds[portalIndex], uint32_t(portalIndex));

	}

	blockManager_ = make_shared<BlockManager>();
	blockManager_->Initialize();
	gameCollisionManager_ = make_unique<BoxCollisionManager>();
	gravityManager_ = make_unique<GravityManager>();

	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;
	gameObjectManager_->Update();
	isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();
	SkyBox::GetInstance()->Reset();
	const float kSkyBoxScale_ = 256.0f;
	SkyBox::GetInstance()->SetTransform({ {kSkyBoxScale_,kSkyBoxScale_,kSkyBoxScale_} });
	uint32_t skyBoxTexHandle = TextureManager::LoadDDSTexture("SkyBox/CubeMap.dds");
	SkyBox::GetInstance()->SetTexHandle(skyBoxTexHandle);
	player_->Update();

}

void SelectScene::Update(GameManager* Scene)
{
	Scene;

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("t", &light_.position.x);
		ImGui::DragFloat("radious", &light_.radious);
		ImGui::DragFloat("decay", &light_.decay);
		ImGui::DragFloat("intencity", &light_.intencity);

		ImGui::TreePop();
	}


	ChangeSceneAnimation::GetInstance()->ImGuiUpdate();

#endif // _USE_IMGUI
	ChangeSceneAnimation::GetInstance()->Update();

	//�V�[���ؑւ��I�������
	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
		player_->SetStartFlag(true);
	}

	player_->Update();

	for (size_t i = 0; i < portalMax_; i++)
	{
		goals_[i]->Update();
	}
	SkyBox::GetInstance()->Update();
	GoalParticle::GetInstance()->Update();

	blockManager_->Update();

	LightingManager::AddList(light_);

	Gravitys();

	Collision();

	gameObjectManager_->Update();

	if (CheckLoadScene())
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		player_->SetStartFlag(false);
	}

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeScene(make_unique<GameScene>());
		return;
	}

	gameCollisionManager_->End();

}

void SelectScene::PostProcessDraw()
{
	SkyBox::GetInstance()->Draw();
	gameObjectManager_->Draw();

	GoalParticle::GetInstance()->Draw();
}

void SelectScene::Back2dSpriteDraw()
{
}

void SelectScene::Object3dDraw()
{
	PostEffect::GetInstance()->Draw();
}

void SelectScene::Flont2dSpriteDraw()
{
	player_->Draw2d();
	ChangeSceneAnimation::GetInstance()->Draw();
}

void SelectScene::Collision()
{
	//�v���C���[�{��
	if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>())
	{
		gameCollisionManager_->ListPushback(player_->GetPlayerCore(), player_->GetPlayerCore());
	}
	//player�̒e
	for (size_t index = 0; index < player_->GetBullet().size(); index++)
	{
		if (player_->GetBullet()[index]) {
			gameCollisionManager_->ListPushback(player_->GetBullet()[index].get(), player_->GetBullet()[index].get());
		}
	}
	//�u���b�N
	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get(), b.get());
	}
	//portal
	for (shared_ptr<Goal>g : goals_)
	{
		gameCollisionManager_->ListPushback(g.get(), g.get());
	}

	gameCollisionManager_->CheckAllCollisoin();

}

void SelectScene::Gravitys()
{
	gravityManager_->ClearList();

	if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>())
	{
		gravityManager_->PushList(player_->GetPlayerCore());
	}

	gravityManager_->CheckGravity();
}

bool SelectScene::CheckLoadScene()
{
	bool changeFlag = false;

	//�v���C���[�Ɠ�������id��portalId����v���Ă����ꍇ
	queue<uint32_t>allHitIds = player_->GetPlayerCore()->GetAllHitIds();
	size_t size = allHitIds.size();

	for (size_t id = 0; id < size; id++)
	{
		uint32_t hitId = allHitIds.front();
		allHitIds.pop();
		for (size_t portalCount = 0; portalCount < portalMax_; portalCount++)
		{
			if (hitId == kPortalIds[portalCount])
			{
				changeFlag = true;
			}
		}
	}
	return changeFlag;
}
