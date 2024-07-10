#include"GameScene.h"

void GameScene::Initialize()
{
	PostEffect::GetInstance()->Initialize("p");

	//levelData‚Ì“Ç‚Ýž‚Ý
	levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_2.json");

	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	camera_.translation_.y = 2.0f;
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	camera_.UpdateMatrix();

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset("PlayerCamera");
	CameraManager::GetInstance();
	gameObjectManager_->Update();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();

	light_.radious = 128.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;

	player_ = make_unique<PlayerManager>();
	player_->GetData(GameObjectManager::GetInstance());

	enemyWalkManager_ = make_unique<EnemyWalkManager>();
	enemyWalkManager_->Initialize(GameObjectManager::GetInstance());

	blockManager_ = make_shared<BlockManager>();
	blockManager_->CopyData(GameObjectManager::GetInstance());
	blockManager_->Initialize();

	gravityManager_ = make_shared<GravityManager>();

}

void  GameScene::Update(GameManager* Scene)
{
#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	debugCamera_->ImGuiUpdate();
	player_->ImGuiUpdate();

	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("t", &light_.position.x);
		ImGui::TreePop();
	}

	if (ImGui::Button("SceneReload"))
	{
		Scene->ChangeState(new  GameScene());
		return;
	}

#endif // _USE_IMGUI

	player_->Update();

	enemyWalkManager_->Update();

	blockManager_->Update();

	Gravitys();

	Collision();

	gameObjectManager_->ObjDataUpdate(player_->GetPlayerCore());
	gameObjectManager_->ObjDataUpdate(player_->GetReticle());
	gameObjectManager_->ObjDataUpdate(player_->GetGun());
	gameObjectManager_->CameraUpdate(player_->GetCamera());

	for (shared_ptr<PlayerBullet> &b : player_->GetBullet()) {
		gameObjectManager_->ObjDataUpdate(b.get());
	}

	gameObjectManager_->InstancingObjDataUpdate(blockManager_->GetTransforms(),"Map");

	gameObjectManager_->Update();

	debugCamera_->Update();

	GameObjectManager::GetInstance();
	LightingManager::AddList(light_);
	PostEffect::GetInstance()->Update();

}

void  GameScene::PostProcessDraw()
{
	PostEffect::GetInstance()->PreDraw();

	gameObjectManager_->Draw();

	PostEffect::GetInstance()->PostDraw();
}

void  GameScene::Back2dSpriteDraw()
{
}

void  GameScene::Object3dDraw()
{
	PostEffect::GetInstance()->Draw(camera_);
}

void  GameScene::Flont2dSpriteDraw()
{
	player_->Draw2d();
}

void  GameScene::Collision()
{
	gameCollisionManager_->ListClear();

	gameCollisionManager_->ListPushback(player_->GetPlayerCore());

	for (size_t index = 0; index < player_->GetBullet().size(); index++)
	{
		if (player_->GetBullet()[index]) {
			gameCollisionManager_->ListPushback(player_->GetBullet()[index].get());
		}
	}
	for (shared_ptr<EnemyWalk>e : enemyWalkManager_->GetData())
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

void  GameScene::Gravitys()
{
	gravityManager_->ClearList();
	gravityManager_->PushList(player_->GetPlayerCore());

	for (shared_ptr<EnemyWalk>e : enemyWalkManager_->GetData())
	{
		if (e)
		{
			gravityManager_->PushList(e.get());
		}
	}

	gravityManager_->CheckGravity();
}
