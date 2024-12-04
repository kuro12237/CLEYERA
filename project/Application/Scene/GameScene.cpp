#include "GameScene.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameScene::Initialize([[maybe_unused]] GameManager* state)
{

	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/GameScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/GameScene/");

	//levelDataの読み込み
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->MoveData(levelData.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();

	light_.radious = 1024.0f;
	light_.position.y = 128.0f;
	light_.position.z = -64.0f;
	light_.decay = 0.1f;


	//Particle初期化
	ParticlesInitialize();

	GoalParticle::GetInstance()->Clear();

	player_ = make_unique<PlayerManager>();
	player_->Initialize();
	
	enemyWalkManager_ = make_unique<EnemyWalkManager>();
	enemyWalkManager_->Initialize();

	bulletEnemyManager_ = make_unique<GunEnemyManager>();
	bulletEnemyManager_->Initialize();

	blockManager_ = make_shared<BlockManager>();
	blockManager_->Initialize();

	breakBlockManager_ = make_unique<BreakBlockManager>();
	breakBlockManager_->Initialize();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();
	gravityManager_ = make_unique<GravityManager>();

	goal_ = make_unique<Goal>();
	goal_->Initialize(kGoalId, 0);

	warpManager_ = make_unique<WarpManager>();
	warpManager_->Initialize();

	stageCoinManager_ = make_unique<StageCoinManager>();
	stageCoinManager_->Initialize();

	//2dObj
	startAnimation_ = make_unique<StartAnimation>();
	startAnimation_->Initialize();

	endAnimation_ = make_unique<EndAnimation>();
	endAnimation_->Initialize();

	gameUi_ = make_unique<GameSceneUI>();
	gameUi_->Initialize();

	//更新
	gameObjectManager_->Update();
	LightingManager::AddList(light_);

	//ゲーム終了のつなぐ
	isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();


	this->SetFlont2dSpriteDrawFunc(std::bind(&GameScene::Flont2dSpriteDraw, this));
	this->SetPostEffectDrawFunc(std::bind(&GameScene::PostProcessDraw, this));

	context_ = make_unique<ISceneContext>();

}

void GameScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	ImGuiUpdate();
	string bottonTitle = "Select_" + inputLevelDataFileName_;
	if (ImGui::Button(bottonTitle.c_str()))
	{
		Scene->ChangeScene(make_unique<GameScene>());

		return;
	}
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
		bulletEnemyManager_->setIsStartFlag(true);
		player_->SetStartFlag(true);
	}

	startAnimation_->Update();
	endAnimation_->Update();

	//
	//ゲーム開始後
	//

	gameUi_->Update();

	player_->Update();

	enemyWalkManager_->Update();
	bulletEnemyManager_->Update();

	blockManager_->Update();
	breakBlockManager_->Update();

	stageCoinManager_->Update();

	goal_->Update();

	warpManager_->Update();

	Gravitys();

	Collision();

	gameObjectManager_->Update();

	ParticlesUpdate();

	LightingManager::AddList(light_);

	//ゴールしたときplayerのアニメーションが終わったら
	if (*isGameEnd_)
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		enemyWalkManager_->SetIsStartFlag(false);
		player_->SetStartFlag(false);
	}


	///プレイヤーが死んだとき
	if (player_->GetPlayerCore()->GetIsDeadAnimationComplite())
	{
		//シーン切り替え開始
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		//ビネットが出ていたら消す
		PostEffect::GetInstance()->SetSelectPostEffect(VIGNETTE, false);

		endAnimation_->SetIsCountStart(true);
		//object設定
		enemyWalkManager_->SetIsStartFlag(false);
		player_->SetStartFlag(false);
		player_->GetPlayerCore()->SetIsGameEnd(true);
	}

	//終わりのアニメーションが終わったら
	if (endAnimation_->GetCompleteFlag())
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
	}

	if (player_->GetHp()->GetHp() <= 0 && ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeScene(make_unique<GameOverScene>());
		return;
	}
	//切替
	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		contextData_.stageConinsCount = stageCoinManager_->GetCoinsCount();
		context_->SetData(contextData_);

		Scene->SetMoveSceneContext(move(context_));
		Scene->ChangeScene(make_unique<GameClearScene>());
		return;
	}

	gameCollisionManager_->End();

}

void GameScene::PostProcessDraw()
{

	gameObjectManager_->InstancingDraw();
	gameObjectManager_->NormalDraw();

	ParticlesDraw();

}

void GameScene::Flont2dSpriteDraw()
{
	
	if (startAnimation_->GetIsGameStartFlag())
	{
		player_->Draw2d();
		player_->DrawHp();
		gameUi_->Draw2d();
	}
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

	this->gameUi_->ImGuiUpdate();


}

void GameScene::Collision()
{
	if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>())
	{
		gameCollisionManager_->ListPushback(player_->GetPlayerCore(), player_->GetPlayerCore());
	}
	for (size_t index = 0; index < player_->GetBullet().size(); index++)
	{
		if (player_->GetBullet()[index]) {
			gameCollisionManager_->ListPushback(player_->GetBullet()[index].get(), player_->GetBullet()[index].get());
		}
	}

	for (shared_ptr<StageCoin>& coin : stageCoinManager_->GetCoins())
	{
		if (coin)
		{
			gameCollisionManager_->ListPushback(coin.get(), coin.get());
		}

	}

	for (shared_ptr<GunEnemy>& e : bulletEnemyManager_->GetGunEnemys())
	{
		weak_ptr<GunEnemy>obj = e;
		auto it = obj.lock();
		if (!it)
		{
			continue;
		}
		gameCollisionManager_->ListPushback(e.get(), e.get());


		for (shared_ptr<GunEnemyBullet>& b : it->GetBullets())
		{
			if (b)
			{
				gameCollisionManager_->ListPushback(b.get(), b.get());
			}

		}
	}

	//歩く敵
	for (shared_ptr<EnemyWalk>& e : enemyWalkManager_->GetData())
	{
		weak_ptr<EnemyWalk>obj = e;
		auto it = obj.lock();
		if (it)
		{
			gameCollisionManager_->ListPushback(it.get(), it.get());
		}
	}

	//ブロック
	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get(), b.get());
	}
	//壊れるブロック
	for (shared_ptr<BreakBlock> b : breakBlockManager_->GetBlocks())
	{
		if (b)
		{
			weak_ptr<BreakBlock>it = b;
			auto obj = it.lock();
			gameCollisionManager_->ListPushback(obj.get(), obj.get());
		}
	}
	//ゴール
	gameCollisionManager_->ListPushback(goal_.get(), goal_.get());

	//ワープ
	for (auto& warp : warpManager_->GetWarps())
	{
		gameCollisionManager_->ListPushback(warp->GetWarpGate(), warp->GetWarpGate());
	}

	gameCollisionManager_->CheckAllCollisoin();

}

void GameScene::Gravitys()
{
	gravityManager_->ClearList();

	if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>())
	{
		if (player_->GetPlayerCore()->GetIsUseGravityFlag())
		{
			gravityManager_->PushList(player_->GetPlayerCore());
		}
	}

	for (shared_ptr<GunEnemy>& e : bulletEnemyManager_->GetGunEnemys())
	{
		if (e)
		{
			gravityManager_->PushList(e.get());
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

void GameScene::PlayUpdate()
{
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
	warpManager_->DebugDraw();


	GoalParticle::GetInstance()->Draw();
	characterDeadParticle_->Draw();
	//characterMoveParticle_->Draw();
	player_->DrawParticle();
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
