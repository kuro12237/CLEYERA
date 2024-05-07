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

	itemManager_ = make_unique<ItemManager>();
	itemManager_->Initialize();

}

void GameScene::Update(GameManager* Scene)
{
	Scene;
#ifdef _USE_IMGUI

	if (ImGui::TreeNode("Control"))
	{
		ImGui::Text("LJoy : Move");
		ImGui::Text("RJoy : ReticleMove");
		ImGui::Text("Botton A : Jamp");
		ImGui::TreePop();
	}

	sun_->ImGuiUpdate();
	player_->ImGuiUpdate();
	blockManager_->UpdateImGui();

#endif // _USE_IMGUI

#pragma region Player

	playerInputHandler_->Handler();
	playerInputHandler_->CommandsExc(*player_);

	player_->Update();

	if (player_->GetHp() == 2)
	{
		//postEffect_->SetGrayFactor(0.5f);
	}
	if (player_->GetHp() == 1)
	{
		//postEffect_->SetGrayFactor(1.0f);
	}

#pragma endregion

	itemManager_->Update();
	itemManager_->Animation();

	blockManager_->Update();

	//MapのUpdate
	MapObjectUpdate();

	//block以外の当たり判定
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
	itemManager_->Draw(cameraData_);

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
	player_->Draw2d(cameraData_);
}

void GameScene::LoadSounds()
{
	AudioManager::GetInstance()->SoundLoadMp3("Resources/Sounds/Jump.mp3");
	AudioManager::GetInstance()->SoundLoadMp3("Resources/Sounds/GetItem.mp3");
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
	
	for (shared_ptr<Item>item : itemManager_->GetItems())
	{
		collsionManager_->ColliderOBBPushBack(item.get());
	}

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

	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize();
}

void GameScene::MapObjectUpdate()
{
	sun_->Update();
	terrain_->Update();
	skyDome_->Update();
}

void GameScene::MapObjectDraw()
{
	terrain_->Draw(cameraData_);
	skyDome_->Draw(cameraData_);
}
