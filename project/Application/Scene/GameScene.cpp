#include "GameScene.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameScene::Initialize([[maybe_unused]] GameManager* state)
{
	//paramfilePath変更
	globalVariables_->SetDirectoryFilePath("Resources/LevelData/ParamData/GameScene/");
	globalVariables_->LoadFiles("Resources/LevelData/ParamData/GameScene/");
	//selectからのデータ
	SceneContextData data;
	data = *state->GetMoveSceneContext()->GetData<SceneContextData>();

	//levelDataの読み込み
	inputLevelDataFileName_ = "LevelData_" + to_string(data.stageNumber + 1) + ".json";
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

	changeSceneAnmation_ = ChangeSceneAnimation::GetInstance();

	gameObjectManager_->ClearAllData();
	gameObjectManager_->MoveData(levelData.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();

	//Particle初期化
	ParticlesInitialize();

	GoalParticle::GetInstance()->Clear();
	CharacterDeadParticle::GetInstance()->GetEmitter()->AllClear();
	CharacterDeadParticle::GetInstance()->GetParticle()->Clear();

	player_ = make_unique<PlayerManager>();
	managerList_.push_back(player_.get());

	enemyWalkManager_ = make_unique<EnemyWalkManager>();
	managerList_.push_back(enemyWalkManager_.get());

	bulletEnemyManager_ = make_unique<GunEnemyManager>();
	managerList_.push_back(bulletEnemyManager_.get());

	blockManager_ = make_unique<BlockManager>();
	managerList_.push_back(blockManager_.get());

	breakBlockManager_ = make_unique<BreakBlockManager>();
	managerList_.push_back(breakBlockManager_.get());

	warpManager_ = make_unique<WarpManager>();
	managerList_.push_back(warpManager_.get());

	stageCoinManager_ = make_unique<StageCoinManager>();
	managerList_.push_back(stageCoinManager_.get());

	gravityManager_ = make_unique<GravityManager>();
	managerList_.push_back(gravityManager_.get());

	for (IManagerList* manager : managerList_)
	{
		manager->Initialize();
	}

	//2dObj
	startAnimation_ = make_unique<StartAnimation>();
	startAnimation_->Initialize(data.stageNumber);

	endAnimation_ = make_unique<EndAnimation>();
	endAnimation_->Initialize();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();

	goal_ = make_unique<Goal>();
	goal_->SetGoalIndex(0);
	goal_->SetGoalObjectId(ObjectId::kGoalId);

	objctDataList_.push_back(goal_.get());

	lava_ = make_unique<Lava>();
	lava_->Initialize();
	objctDataList_.push_back(lava_.get());

	for (IObjectData* data : objctDataList_)
	{
		data->Initialize();
	}

	light_ = make_unique<GameLight>();
	light_->Initialize();

	gameUi_ = make_unique<GameSceneUI>();
	gameUi_->Initialize();

	//ゲーム終了のつなぐ
	isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();

	this->SetFlont2dSpriteDrawFunc(std::bind(&GameScene::Flont2dSpriteDraw, this));
	this->SetPostEffectDrawFunc(std::bind(&GameScene::PostProcessDraw, this));

	context_ = make_unique<ISceneContext>();

	wallHitParticle_ = make_unique<WallHitParticle>();
	wallHitParticle_->Initialize();
	particleList_.push_back(wallHitParticle_.get());


	PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_ = 1.0f;
	PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_ = 1.0f;
	PostEffect::GetInstance()->GetAdjustedColorParam().fogStart = 200.0f;
	PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd = 900.0f;
}

void GameScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	ImGui::Begin("PostEffect");
	ImGui::DragFloat("scale::%f", &PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_, 0.01f);
	ImGui::DragFloat("att::%f", &PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_, 0.01f);
	ImGui::DragFloat("start::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogStart, 1.0f);
	ImGui::DragFloat("end::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd, 1.0f);
	ImGui::End();


	ImGuiUpdate();
	string bottonTitle = "Select_" + inputLevelDataFileName_;
	if (ImGui::Button(bottonTitle.c_str()))
	{
		Scene->ChangeScene(make_unique<GameScene>());
		return;
	}
#endif // _USE_IMGUI

	changeSceneAnmation_->Update();

	//シーン切替が終わったら
	if (changeSceneAnmation_->GetIsComplite())
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

	for (IManagerList* it : managerList_)
	{
		it->Update();
	}

	goal_->Update();
	lava_->Update();

	Gravitys();
	Collision();

	gameObjectManager_->Update();

	ParticlesUpdate();

	light_->Update();

	if (CheckChangeScene(Scene)) {
		return;
	}

	gameCollisionManager_->End();

}

bool GameScene::CheckChangeScene(GameManager* Scene)
{
	//ゴールしたときplayerのアニメーションが終わったら
	if (*isGameEnd_)
	{
		changeSceneAnmation_->ChangeStart();

		enemyWalkManager_->SetIsStartFlag(false);
		player_->SetStartFlag(false);
	}

	///プレイヤーが死んだとき
	if (player_->GetPlayerCore()->GetIsDeadAnimationComplite())
	{
		//シーン切り替え開始
		changeSceneAnmation_->ChangeStart();

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
		changeSceneAnmation_->ChangeStart();
	}

	if (player_->GetHp()->GetHp() <= 0 && changeSceneAnmation_->GetIsChangeSceneFlag())
	{
		Scene->ChangeScene(make_unique<GameOverScene>());
		return true;
	}
	//切替
	if (changeSceneAnmation_->GetIsChangeSceneFlag())
	{
		contextData_.stageConinsCount = stageCoinManager_->GetCoinsCount();
		context_->SetData(contextData_);

		Scene->SetMoveSceneContext(move(context_));
		Scene->ChangeScene(make_unique<GameClearScene>());
		return true;
	}
	return false;
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
		player_->Draw2dBullet();
		player_->DrawHp();
		gameUi_->Draw2d();
	}
	startAnimation_->Draw2d();
	changeSceneAnmation_->Draw();
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

	player_->ImGuiUpdate();

	ParticleImGuiUpdate();
	changeSceneAnmation_->ImGuiUpdate();

	this->gameUi_->ImGuiUpdate();

}

void GameScene::Collision()
{
	if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>())
	{
		gameCollisionManager_->ListPushback(player_->GetPlayerCore());
	}
	for (size_t index = 0; index < player_->GetBullet().size(); index++)
	{
		if (player_->GetBullet()[index]) {
			gameCollisionManager_->ListPushback(player_->GetBullet()[index].get());
		}
	}

	for (shared_ptr<StageCoin>& coin : stageCoinManager_->GetCoins())
	{
		if (coin)
		{
			gameCollisionManager_->ListPushback(coin.get());
		}
	}

	if (bulletEnemyManager_->GetIsStartFlag())
	{
		for (auto& enemy : bulletEnemyManager_->GetGunEnemys())
		{
			weak_ptr<GunEnemy>obj = enemy.core;
			auto it = obj.lock();
			if (it)
			{
				gameCollisionManager_->ListPushback(it.get());

				for (shared_ptr<GunEnemyBullet>& b : it->GetBullets())
				{
					if (b)
					{
						gameCollisionManager_->ListPushback(b.get());
					}

				}
			}

			for (auto& parts : enemy.parts)
			{
				if (!parts)
				{
					continue;
				}
				if (parts->GetIsEnd())
				{
					gameCollisionManager_->ListPushback(parts.get());
				}
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
			gameCollisionManager_->ListPushback(it.get());
		}
	}

	//ブロック
	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get());
	}
	//壊れるブロック
	for (shared_ptr<BreakBlock> b : breakBlockManager_->GetBlocks())
	{
		if (b)
		{
			weak_ptr<BreakBlock>it = b;
			auto obj = it.lock();
			gameCollisionManager_->ListPushback(obj.get());
		}
	}
	//ゴール
	gameCollisionManager_->ListPushback(goal_.get());

	//ワープ
	for (auto& warp : warpManager_->GetWarps())
	{
		gameCollisionManager_->ListPushback(warp->GetWarpGate());
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

	if (bulletEnemyManager_->GetIsStartFlag())
	{
		for (auto& e : bulletEnemyManager_->GetGunEnemys())
		{
			if (e.core)
			{
				gravityManager_->PushList(e.core.get());
			}
			for (auto& parts : e.parts)
			{
				if (!parts)
				{
					continue;
				}
				if (parts->GetIsEnd())
				{
					gravityManager_->PushList(parts.get());
				}
			}
		}
	}

	if (enemyWalkManager_->GetIsStartFlag())
	{
		for (shared_ptr<EnemyWalk>& e : enemyWalkManager_->GetData())
		{
			if (e)
			{
				gravityManager_->PushList(e.get());
			}
		}
	}
	gravityManager_->PushParticleList(CharacterDeadParticle::GetInstance()->GetParticle());
	gravityManager_->PushParticleList(lava_->GetLavaParticle()->GetParticle());

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
	characterDeadParticle_->GetParticle()->CallBarrier();
	blockManager_->Dispach(characterDeadParticle_->GetParticle());

	characterDeadParticle_->Update();

	characterMoveParticle_->Update();
	wallHitParticle_->Update();

	GoalParticle::GetInstance()->Update();


}

void GameScene::ParticlesDraw()
{
	warpManager_->DebugDraw();

	GoalParticle::GetInstance()->Draw();
	characterDeadParticle_->Draw();
	lava_->GetLavaParticle()->Draw();

	wallHitParticle_->Draw();

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
