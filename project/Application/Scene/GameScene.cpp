#include "GameScene.h"

using namespace Engine::Manager;

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


	//Particle初期化
	ParticlesInitialize();

	GoalParticle::GetInstance()->Clear();

	player_ = make_unique<PlayerManager>();
	player_->Initialize();

	enemyWalkManager_ = make_unique<EnemyWalkManager>();
	enemyWalkManager_->Initialize();

	blockManager_ = make_shared<BlockManager>();
	blockManager_->Initialize();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();
	gravityManager_ = make_unique<GravityManager>();

	goal_ = make_unique<Goal>();
	goal_->Initialize(kGoalId, 0);

	//2dObj
	startAnimation_ = make_unique<StartAnimation>();
	startAnimation_->Initialize();

	warp_ = make_unique<Warp>();
	warp_->Initlaize();

	//更新
	gameObjectManager_->Update();

	LightingManager::AddList(light_);

	//ゲーム終了のつなぐ
	isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();

}

void GameScene::Update([[maybe_unused]] GameManager* Scene)
{

#ifdef _USE_IMGUI

	ImGuiUpdate();

	warp_->ImGuiUpdate();

#endif // _USE_IMGUI

	ChangeSceneAnimation::GetInstance()->Update();

	//シーン切替が終わったら
	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
		startAnimation_->SetIsCountStart(true);
	}

	//カウントダウンが終わったら
	if (startAnimation_->GetIsGameStartFlag())
	{
		enemyWalkManager_->SetIsStartFlag(true);
		player_->SetStartFlag(true);
	}

	startAnimation_->Update();

	//
	//ゲーム開始後
	//

	player_->Update();

	enemyWalkManager_->Update();

	blockManager_->Update();

	goal_->Update();

	warp_->Update();

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
		enemyWalkManager_->SetIsStartFlag(false);
		player_->SetStartFlag(false);
	}

	if (player_->GetHp()->GetHp() <= 0)
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		PostEffect::GetInstance()->SetSelectPostEffect(VIGNETTE, false);
		enemyWalkManager_->SetIsStartFlag(false);
		player_->SetStartFlag(false);
	}

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeScene(make_unique<TitleScene>());
		return;
	}

	gameCollisionManager_->End();

}

void GameScene::PostProcessDraw()
{

	gameObjectManager_->Draw();

	ParticlesDraw();
	warp_->DebugDrawLine();

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
	player_->DrawHp();
	startAnimation_->Draw2d();
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
	ChangeSceneAnimation::GetInstance()->ImGuiUpdate();
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

	gameCollisionManager_->ListPushback(warp_->GetWarpGate());

	gameCollisionManager_->CheckAllCollisoin();

}

void GameScene::Gravitys()
{
	gravityManager_->ClearList();

	if (!player_->GetPlayerCore()->GetIsGoal())
	{
		if (player_->GetPlayerCore()->GetIsUseGravityFlag())
		{
			gravityManager_->PushList(player_->GetPlayerCore());
		}
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
	if (ImGui::TreeNode("Particles"))
	{
		GoalParticle::GetInstance()->ImGuiUpdate();
		characterDeadParticle_->ImGuiUpdate();
		characterMoveParticle_->ImGuiUpdate();
		ImGui::TreePop();
	}
}
