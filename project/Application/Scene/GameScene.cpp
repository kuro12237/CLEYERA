#include "GameScene.h"

void GameScene::Initialize()
{

	//levelDataの読み込み
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_);

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();

	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;

	//SkyBox
	const float kSkyBoxScale = 256.0f;
	SkyBox::GetInstance()->SetTransform({ {kSkyBoxScale,kSkyBoxScale,kSkyBoxScale},{},{} });

	//3dObj
	ParticlesInitialize();

	GoalParticle::GetInstance()->Clear();

	player_ = make_unique<PlayerManager>();
	player_->GetData(GameObjectManager::GetInstance());

	enemyWalkManager_ = make_unique<EnemyWalkManager>();
	enemyWalkManager_->Initialize(GameObjectManager::GetInstance());

	blockManager_ = make_shared<BlockManager>();
	blockManager_->Initialize();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();
	gravityManager_ = make_unique<GravityManager>();

	goal_ = make_unique<Goal>();
	goal_->Initialize(kGoalId,0);

	//2dObj
	startCount_ = make_unique<StartCount>();
	startCount_->Initialize();

	//更新
	gameObjectManager_->Update();

	LightingManager::AddList(light_);

	uint32_t skyBoxTexHandle = TextureManager::LoadDDSTexture("SkyBox/navyBlue.dds");
	SkyBox::GetInstance()->SetTexHandle(skyBoxTexHandle);

	isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();

}

void GameScene::Update([[maybe_unused]] GameManager* Scene)
{

#ifdef _USE_IMGUI

	ImGuiUpdate();

#endif // _USE_IMGUI

	
	ChangeSceneAnimation::GetInstance()->Update();

	//シーン切替が終わったら
	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
		startCount_->Update();
	}

	//カウントダウンが終わったら
	if (startCount_->GetStartFlag())
	{
		enemyWalkManager_->SetStatFlag(true);
		player_->SetStartFlag(true);
		startCount_->SetStartFlag(false);
	}

	//
	//ゲーム開始後
	//

	player_->Update();

	enemyWalkManager_->Update();

	blockManager_->Update();

	goal_->Update();

	Gravitys();

	Collision();

	gameObjectManager_->Update();

	ParticlesUpdate();

	LightingManager::AddList(light_);
	PostEffect::GetInstance()->Update();

	//playerのアニメーションが終わったら
	if (*isGameEnd_)
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		enemyWalkManager_->SetStatFlag(false);
		player_->SetStartFlag(false);
	}

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeState(new TitleScene);
		return;
	}
	gameCollisionManager_->End();

}

void GameScene::PostProcessDraw()
{

	gameObjectManager_->Draw();

	ParticlesDraw();
	
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	PostEffect::GetInstance()->Draw();
}

void GameScene::Flont2dSpriteDraw()
{
	player_->Draw2d();
	startCount_->Draw2d();
	ChangeSceneAnimation::GetInstance()->Draw();
}

void GameScene::ImGuiUpdate()
{
	gameObjectManager_->ImGuiUpdate();
	ImGui::Separator();
	ImGui::Text("SceneReload");
	static char buffer[256] = "";
	if (ImGui::InputText("SelectLevelDataFilePath", buffer, sizeof(buffer)))
	{
		inputLevelDataFileName_ = std::string(buffer);
	}
	string bottonTitle = "Select_" + inputLevelDataFileName_;
	if (ImGui::Button(bottonTitle.c_str()))
	{
		Initialize();
		return;
	}

	ImGui::Separator();
	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("t", &light_.position.x);
		ImGui::DragFloat("radious", &light_.radious);
		ImGui::DragFloat("decay", &light_.decay);
		ImGui::DragFloat("intencity", &light_.intencity);

		ImGui::TreePop();
	}

	player_->ImGuiUpdate();

	ParticleImGuiUpdate();

}

void GameScene::Collision()
{
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

	for (shared_ptr<EnemyWalk>& e : enemyWalkManager_->GetData())
	{
		if (e)
		{
			gameCollisionManager_->ListPushback(e.get());
		}
	}

	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get());
	}


	gameCollisionManager_->ListPushback(goal_.get());

	gameCollisionManager_->CheckAllCollisoin();

}

void GameScene::Gravitys()
{
	gravityManager_->ClearList();

	if (!player_->GetPlayerCore()->GetIsGoal())
	{
		gravityManager_->PushList(player_->GetPlayerCore());
	}
	for (shared_ptr<EnemyWalk>& e : enemyWalkManager_->GetData())
	{
		if (e)
		{
			gravityManager_->PushList(e.get());
		}
	}
	gravityManager_->CheckGravity();
}

void GameScene::ParticlesInitialize()
{
	characterDeadParticle_ = CharacterDeadParticle::GetInstance();
	characterDeadParticle_->Initialize();

	characterMoveParticle_ = CharacterMoveParticle::GetInstance();
	characterMoveParticle_->Initialize();
}

void GameScene::ParticlesUpdate()
{
	characterDeadParticle_->Update();
	characterMoveParticle_->Update();
	GoalParticle::GetInstance()->Update();

}

void GameScene::ParticlesDraw()
{
	GoalParticle::GetInstance()->Draw();
	characterDeadParticle_->Draw();
	characterMoveParticle_->Draw();
}

void GameScene::ParticleImGuiUpdate()
{
	if(ImGui::TreeNode("Particles"))
	{
		GoalParticle::GetInstance()->ImGuiUpdate();
		characterDeadParticle_->ImGuiUpdate();
		characterMoveParticle_->ImGuiUpdate();
		ImGui::TreePop();
	}
}
