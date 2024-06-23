#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
{
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("testScene");

	//levelDataの読み込み
	levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_1.json");

	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	camera_.translation_.y = 2.0f;
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	camera_.UpdateMatrix();
	CameraManager::GetInstance()->ResetCamera(camera_);

	//オブジェクト管理クラスの作成
	objectManager_ = make_unique<GameObjectManager>();
	objectManager_->CopyData(levelData_.get());

	gameCollisionManager_ = make_unique<BoxCollisionManager>();

	light_.radious = 128.0f;
	light_.position.y = 64.0f;
	light_.decay = 0.1f;

	player_ = make_shared<Player>();
	player_->Initialize();
	player_->GetData(objectManager_.get());

	enemyWalk_ = make_shared<EnemyWalk>();
	enemyWalk_->Initialize();
	enemyWalk_->GetData(objectManager_.get());

	blockManager_ = make_shared<BlockManager>();
	blockManager_->CopyData(objectManager_.get());
	blockManager_->Initialize();
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

#endif // _USE_IMGUI

	player_->Update();

	enemyWalk_->Update();

	blockManager_->Update();

	Collision();

	objectManager_->ObjDataUpdate(player_.get());
	objectManager_->ObjDataUpdate(enemyWalk_.get());
	objectManager_->InstancingObjDataUpdate(blockManager_->GetTransforms(), "Map");

	objectManager_->Update();

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);

	LightingManager::AddList(light_);
	postEffect_->Update();
}

void TestLevelDataScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	objectManager_->Draw();

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

	gameCollisionManager_->ListPushback(player_.get());
	gameCollisionManager_->ListPushback(enemyWalk_.get());
	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get());
	}
	gameCollisionManager_->CheckAllCollisoin();

}
