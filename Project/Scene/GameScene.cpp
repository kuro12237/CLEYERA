#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData_.Initialize();

	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize(sceneName_);

	MapObjectInitialize();

	woodBlockManager_ = make_unique<WoodBlockManager>();
	woodBlockManager_->Initialize();

	blockCollisionManager_ = make_unique<GameCollisonManager>();

	gravityManager_ = make_unique<GameGravityManager>();

	player_ = make_unique<Player>();
	player_->Initialize();
	player_->Update();

	playerCamera_ = make_unique<PlayerCamera>();
	playerCamera_->Initialize();
	playerCamera_->SetParent(player_->GetWorldTransform());

	playerInputHandler_ = make_unique<PlayerInputHandler>();

}

void GameScene::Update(GameManager* Scene)
{
	Scene;
#ifdef _USE_IMGUI

	sun_->ImGuiUpdate();
	player_->ImGuiUpdate();
#endif // _USE_IMGUI

#pragma region

	playerInputHandler_->Handler();
	playerInputHandler_->CommandsExc(*player_);

	player_->Update();

#pragma endregion

	woodBlockManager_->Update();

	MapObjectUpdate();

	//CheckGravitys();
	//blockの当たり判定
	CheckBlockCollision();

	playerCamera_->Update();
	cameraData_ = playerCamera_->GetData();
	cameraData_.TransfarMatrix();

	postEffect_->Update();
}

void GameScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	player_->Draw(cameraData_);
	woodBlockManager_->Draw(cameraData_);

	postEffect_->PostDraw();

}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
}

void GameScene::Flont2dSpriteDraw()
{
	postEffect_->Draw(cameraData_);
}

void GameScene::CheckBlockCollision()
{
	blockCollisionManager_->ClearList();
	
	blockCollisionManager_->PushList(player_.get());

	for (int i = 0; i < woodBlockManager_->GetBlocks().size(); i++)
	{
		if (woodBlockManager_->GetBlocks()[i])
		{
			blockCollisionManager_->PushList(woodBlockManager_->GetBlocks()[i].get());
		}
	}

	blockCollisionManager_->CheckAllCollisions();
}

void GameScene::CheckGravitys()
{
	gravityManager_->ClearList();

	gravityManager_->PushList(player_.get());

	gravityManager_->CheckAllGravity();
}

void GameScene::MapObjectInitialize()
{
	sun_ = make_unique<Sun>();
	sun_->Initialize();
}

void GameScene::MapObjectUpdate()
{
	sun_->Update();
}

void GameScene::MapObjectDraw()
{
}
