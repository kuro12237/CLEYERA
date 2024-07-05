#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
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
	CameraManager::GetInstance()->ResetCamera(camera_);

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->Update();

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
#ifdef _USE_IMGUI
	gameObjectManager_->ImGuiUpdate();

	debugCamera_->ImGuiUpdate();

	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("t", &light_.position.x);
		ImGui::TreePop();
	}

	player_->ImGuiUpdate();

	if (ImGui::Button("SceneReload"))
	{
		Scene->ChangeState(new TestLevelDataScene());
		return;
	}
	testBox_->ImGuiUpdate();

#endif // _USE_IMGUI

	player_->Update();


	if (enemyWalk_)
	{
		enemyWalk_->Update();

		gameObjectManager_->ObjDataUpdate(enemyWalk_.get());
		if (enemyWalk_->GetIsDead())
		{
			gameObjectManager_->ClearObj3dData(enemyWalk_->GetName());
			enemyWalk_.reset();
		}

	}

	blockManager_->Update();

	Gravitys();

	Collision();
	
	gameObjectManager_->ObjDataUpdate(testBox_.get());
	gameObjectManager_->ObjDataUpdate(player_->GetPlayerCore());
	gameObjectManager_->ObjDataUpdate(player_->GetReticle());
	gameObjectManager_->ObjDataUpdate(player_->GetGun());

	for (shared_ptr<PlayerBullet> &b : player_->GetBullet()) {
		gameObjectManager_->ObjDataUpdate(b.get());
	}
	gameObjectManager_->InstancingObjDataUpdate(blockManager_->GetTransforms(),"Map");

	gameObjectManager_->Update();

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

	gameObjectManager_->Draw();

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
	gravityManager_->PushList(player_->GetPlayerCore());
	if (enemyWalk_)
	{
		gravityManager_->PushList(enemyWalk_.get());
	}
	gravityManager_->CheckGravity();
}
