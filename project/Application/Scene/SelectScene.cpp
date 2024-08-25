#include "SelectScene.h"

void SelectScene::Initialize()
{
	//levelData‚Ì“Ç‚Ýž‚Ý
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_);

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();

	characterDeadParticle_ = CharacterDeadParticle::GetInstance();
	characterDeadParticle_->Initialize();

	characterMoveParticle_ = CharacterMoveParticle::GetInstance();
	characterMoveParticle_->Initialize();
	player_ = make_unique<PlayerManager>();
	player_->GetData(gameObjectManager_);


	goal_ = make_unique<Goal>();
	goal_->Initialize();

	blockManager_ = make_shared<BlockManager>();
	blockManager_->Initialize();
	gameCollisionManager_ = make_unique<BoxCollisionManager>();
	gravityManager_ = make_unique<GravityManager>();
	//SkyBox
	const float kSkyBoxScale = 256.0f;
	SkyBox::GetInstance()->SetTransform({ {kSkyBoxScale,kSkyBoxScale,kSkyBoxScale},{},{} });
	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;
	gameObjectManager_->Update();
	isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();
}

void SelectScene::Update(GameManager* Scene)
{
	Scene;

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();

#endif // _USE_IMGUI
	ChangeSceneAnimation::GetInstance()->Update();

	//ƒV[ƒ“Ø‘Ö‚ªI‚í‚Á‚½‚ç
	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
		player_->SetStartFlag(true);
	}

	player_->Update();

	goal_->Update();

	blockManager_->Update();

	LightingManager::AddList(light_);

	Gravitys();

	Collision();

	gameObjectManager_->Update();
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_B))
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		player_->SetStartFlag(false);
	}

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeState(new GameScene);
		return;
	}
}

void SelectScene::PostProcessDraw()
{
	gameObjectManager_->Draw();
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
	gameCollisionManager_->ListClear();

	if (!player_->GetPlayerCore()->GetIsGoal())
	{
		gameCollisionManager_->ListPushback(player_->GetPlayerCore());
	}
	for (size_t index = 0; index < player_->GetBullet().size(); index++)
	{
		if (player_->GetBullet()[index]) {
			gameCollisionManager_->ListPushback(player_->GetBullet()[index].get());
		}
	}

	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get());
	}

	gameCollisionManager_->CheckAllCollisoin();

}

void SelectScene::Gravitys()
{
	gravityManager_->ClearList();

	if (!player_->GetPlayerCore()->GetIsGoal())
	{
		gravityManager_->PushList(player_->GetPlayerCore());
	}

	gravityManager_->CheckGravity();
}