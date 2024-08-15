#include "GameScene.h"

void GameScene::Initialize()
{
	PostEffect::GetInstance()->Initialize();

	//levelDataの読み込み
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_);

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();

	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;

	player_ = make_unique<PlayerManager>();
	player_->GetData(GameObjectManager::GetInstance());

	enemyWalkManager_ = make_unique<EnemyWalkManager>();
	enemyWalkManager_->Initialize(GameObjectManager::GetInstance());

	blockManager_ = make_shared<BlockManager>();
	blockManager_->Initialize();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();
	gravityManager_ = make_unique<GravityManager>();

	characterDeadParticle_ = CharacterDeadParticle::GetInstance();
	characterDeadParticle_->Initialize();

	startCount_ = make_unique<StartCount>();
	startCount_->Initialize();


	gameObjectManager_->Update();

	LightingManager::AddList(light_);

	PostEffect::GetInstance()->Update();
}

void GameScene::Update([[maybe_unused]] GameManager* Scene)
{
	Scene;

#ifdef _USE_IMGUI

	ImGuiUpdate();

#endif // _USE_IMGUI

	startCount_->Update();
	
	//カウントダウン中の処理
	if (startCount_->GetStartFlag())
	{
		enemyWalkManager_->SetStatFlag(true);
		player_->SetStartFlag(true);
	}

	characterDeadParticle_->Update();

	//ゲーム開始後
	player_->Update();

	enemyWalkManager_->Update();

	blockManager_->Update();

	Gravitys();

	Collision();

	gameObjectManager_->Update();

	LightingManager::AddList(light_);

	PostEffect::GetInstance()->Update();
}

void GameScene::PostProcessDraw()
{
	PostEffect::GetInstance()->PreDraw();

	gameObjectManager_->Draw();
	characterDeadParticle_->Draw();

	PostEffect::GetInstance()->PostDraw();
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

	characterDeadParticle_->ImGuiUpdate();

}

void GameScene::Collision()
{
	gameCollisionManager_->ListClear();

	gameCollisionManager_->ListPushback(player_->GetPlayerCore());

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
	gameCollisionManager_->CheckAllCollisoin();

}

void GameScene::Gravitys()
{
	gravityManager_->ClearList();
	gravityManager_->PushList(player_->GetPlayerCore());

	for (shared_ptr<EnemyWalk>& e : enemyWalkManager_->GetData())
	{
		if (e)
		{
			gravityManager_->PushList(e.get());
		}
	}
	gravityManager_->CheckGravity();
}
