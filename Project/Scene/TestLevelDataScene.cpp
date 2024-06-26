#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
{
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("testScene");

	//levelData‚Ì“Ç‚Ýž‚Ý
	levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_1.json");

	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	camera_.translation_.y = 2.0f;
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	camera_.UpdateMatrix();
	CameraManager::GetInstance()->ResetCamera(camera_);

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

}

void TestLevelDataScene::Update(GameManager* Scene)
{
	Scene;
#ifdef _USE_IMGUI

	debugCamera_->ImGuiUpdate();

	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("t", &light_.position.x);
		ImGui::TreePop();
	}

	player_->ImGuiUpdate();

#endif // _USE_IMGUI

	player_->Update();

	enemyWalk_->Update();

	blockManager_->Update();

	Gravitys();

	Collision();

	GameObjectManager::GetInstance()->ObjDataUpdate(player_->GetPlayerCore());
	GameObjectManager::GetInstance()->ObjDataUpdate(player_->GetReticle());
	GameObjectManager::GetInstance()->ObjDataUpdate(player_->GetGun());
	GameObjectManager::GetInstance()->ObjDataUpdate(enemyWalk_.get());
	GameObjectManager::GetInstance()->InstancingObjDataUpdate(blockManager_->GetTransforms(),"Map");
	
	GameObjectManager::GetInstance()->Update();

	camera_.translation_ = player_->GetPlayerCore()->GetTransform().translate;
	camera_.translation_.z = camera_.translation_.z - 32.0f;

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);
	camera_.UpdateMatrix();

	LightingManager::AddList(light_);
	postEffect_->Update();
}

void TestLevelDataScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	GameObjectManager::GetInstance()->Draw();

	postEffect_->PostDraw();
}

void TestLevelDataScene::Back2dSpriteDraw()
{
}

void TestLevelDataScene::Object3dDraw()
{
	postEffect_->Draw(camera_);
}

void TestLevelDataScene::Flont2dSpriteDraw()
{
}

void TestLevelDataScene::Collision()
{
	gameCollisionManager_->ListClear();

	gameCollisionManager_->ListPushback(player_->GetPlayerCore());
	gameCollisionManager_->ListPushback(enemyWalk_.get());

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
	gravityManager_->CheckGravity();
}
