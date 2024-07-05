#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
{
	PostEffect::GetInstance()->Initialize("p");

	//levelData‚Ì“Ç‚Ýž‚Ý
	levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_1.json");
	
	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	camera_.translation_.y = 2.0f;
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	camera_.UpdateMatrix();
	CameraManager::GetInstance()->ResetCamera(camera_);

	GameObjectManager* instance = GameObjectManager::GetInstance();
	instance;
	GameObjectManager::GetInstance()->CopyData(levelData_.get());
	GameObjectManager::GetInstance()->SetAllParents();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();

	light_.radious = 128.0f;
	light_.position.y = 64.0f;
	light_.decay = 0.1f;

	player_ = make_unique<PlayerManager>();
	player_->GetData(GameObjectManager::GetInstance());
	
	enemyWalk_ = make_shared<EnemyWalk>();
	enemyWalk_->Initialize();
	enemyWalk_->GetData(GameObjectManager::GetInstance());

	blockManager_ = make_shared<BlockManager>();
	blockManager_->CopyData(GameObjectManager::GetInstance());
	blockManager_->Initialize();

	gravityManager_ = make_shared<GravityManager>();
	ModelManager::LoadObjectFile("PlayerNormalBullet");

	testBox_ = make_shared<CollisionTestBox>();
	testBox_->Initialize();

}

void TestLevelDataScene::Update(GameManager* Scene)
{
	Scene;
	//GameObjectManager* instance = GameObjectManager::GetInstance();
#ifdef _USE_IMGUI
	GameObjectManager* instance = GameObjectManager::GetInstance();
	instance->ImGuiUpdate();

	debugCamera_->ImGuiUpdate();

	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("t", &light_.position.x);
		ImGui::TreePop();
	}

	player_->ImGuiUpdate();

	if (ImGui::Button("SceneReload"))
	{
		instance->ClearAllData();
		levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_1.json");
		instance->CopyData(levelData_.get());
		instance->SetAllParents();
		player_->GetData(instance);
		return;
	}
	testBox_->ImGuiUpdate();

#endif // _USE_IMGUI

	player_->Update();


	if (enemyWalk_)
	{
		enemyWalk_->Update();

		GameObjectManager::GetInstance()->ObjDataUpdate(enemyWalk_.get());
		if (enemyWalk_->GetIsDead())
		{
			GameObjectManager::GetInstance()->ClearObj3dData(enemyWalk_->GetName());
			enemyWalk_.reset();
		}

	}

	blockManager_->Update();

	Gravitys();

	Collision();
	
	GameObjectManager::GetInstance()->ObjDataUpdate(testBox_.get());
	GameObjectManager::GetInstance()->ObjDataUpdate(player_->GetPlayerCore());
	GameObjectManager::GetInstance()->ObjDataUpdate(player_->GetReticle());
	GameObjectManager::GetInstance()->ObjDataUpdate(player_->GetGun());

	for (shared_ptr<PlayerBullet> &b : player_->GetBullet()) {
		GameObjectManager::GetInstance()->ObjDataUpdate(b.get());
	}

	GameObjectManager::GetInstance()->InstancingObjDataUpdate(blockManager_->GetTransforms(),"Map");
	
	GameObjectManager::GetInstance()->Update();

	camera_.translation_ = player_->GetPlayerCore()->GetTransform().translate;
	camera_.translation_.z = camera_.translation_.z - 32.0f;

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);
	camera_.UpdateMatrix();

	LightingManager::AddList(light_);
	PostEffect::GetInstance()->Update();
}

void TestLevelDataScene::PostProcessDraw()
{
	PostEffect::GetInstance()->PreDraw();

	GameObjectManager::GetInstance()->Draw();

	PostEffect::GetInstance()->PostDraw();
}

void TestLevelDataScene::Back2dSpriteDraw()
{
}

void TestLevelDataScene::Object3dDraw()
{
	PostEffect::GetInstance()->Draw(camera_);
}

void TestLevelDataScene::Flont2dSpriteDraw()
{
	player_->Draw2d();
}

void TestLevelDataScene::Collision()
{
	gameCollisionManager_->ListClear();

	gameCollisionManager_->ListPushback(player_->GetPlayerCore());

	for (size_t index = 0; index < player_->GetBullet().size(); index++)
	{
		if (player_->GetBullet()[index]) {
			gameCollisionManager_->ListPushback(player_->GetBullet()[index].get());
		}
	}
	if (enemyWalk_)
	{
		gameCollisionManager_->ListPushback(enemyWalk_.get());
	}
	gameCollisionManager_->ListPushback(testBox_.get());

	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get());
	}
	gameCollisionManager_->CheckAllCollisoin();

}

void TestLevelDataScene::Gravitys()
{
	gravityManager_->ClearList();
	//gravityManager_->PushList(player_->GetPlayerCore());
	if (enemyWalk_)
	{
		gravityManager_->PushList(enemyWalk_.get());
	}
	gravityManager_->CheckGravity();
}
