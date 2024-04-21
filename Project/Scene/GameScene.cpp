#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData_.Initialize();

	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize(sceneName_);

	LoadSounds();
	MapObjectInitialize();

	blockCollisionManager_ = make_unique<GameCollisonManager>();

	gravityManager_ = make_unique<GameGravityManager>();

	player_ = make_unique<Player>();
	player_->Initialize();
	player_->Update();

	playerCamera_ = make_unique<PlayerCamera>();
	playerCamera_->Initialize();
	playerCamera_->SetParent(player_->GetWorldTransform());

	playerInputHandler_ = make_unique<PlayerInputHandler>();

    blockManager_ = make_unique<WoodBlockManager>();
	blockManager_->Initialize();

	item_ = make_unique<Item>();
	item_->Initialize();

}

void GameScene::Update(GameManager* Scene)
{
	Scene;
#ifdef _USE_IMGUI

	sun_->ImGuiUpdate();
	player_->ImGuiUpdate();
	blockManager_->UpdateImGui();

#endif // _USE_IMGUI

#pragma region Player

	playerInputHandler_->Handler();
	playerInputHandler_->CommandsExc(*player_);

	player_->Update();

#pragma endregion

	item_->Update();
	item_->Animation();
	
	blockManager_->Update();

	//MapのUpdate
	MapObjectUpdate();

	//clock以外の当たり判定
	CheckCollision();
	//重力計算
	CheckGravitys();
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
	blockManager_->Draw(cameraData_);
	item_->Draw(cameraData_);

	MapObjectDraw();

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

void GameScene::LoadSounds()
{
	AudioManager::GetInstance()->SoundLoadMp3("Resources/Sounds/Jump.mp3");
}

void GameScene::CheckBlockCollision()
{
	blockCollisionManager_->ClearList();
	
	blockCollisionManager_->PushList(player_.get());

	for (int i = 0; i < blockManager_->GetBlocks().size(); i++)
	{
		if (blockManager_->GetBlocks()[i])
		{
			blockCollisionManager_->PushList(blockManager_->GetBlocks()[i].get());
		}
	}
	blockCollisionManager_->CheckAllCollisions();
}

void GameScene::CheckCollision()
{
	collsionManager_->ClliderClear();
	collsionManager_->ColliderOBBPushBack(item_.get());
	collsionManager_->ColliderOBBPushBack(player_.get());
	collsionManager_->CheckAllCollision();
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

	terrain_ = make_unique<Terrain>();
	terrain_->Initialize();
}

void GameScene::MapObjectUpdate()
{
	sun_->Update();
	terrain_->Update();
}

void GameScene::MapObjectDraw()
{
	terrain_->Draw(cameraData_);
}
