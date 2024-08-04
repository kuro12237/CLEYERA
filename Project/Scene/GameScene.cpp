#include "GameScene.h"

void GameScene::Initialize()
{
	WinApp::GetInstance()->SetTiTleName(L"GunHead");
	PostEffect::GetInstance()->Initialize("p");

	//levelData‚Ì“Ç‚Ýž‚Ý
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_);

	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();

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

	gpuParticle_ = make_unique<Particle::GpuParticle>();
	gpuParticle_->Create(1024, "landParticle");

	uint32_t texHandle = TextureManager::LoadDDSTexture("rostock_laage_airport_4k.dds");
	SkyBox::GetInstance()->Initialize();
	SkyBox::GetInstance()->SetTexHandle(texHandle);
	emitter_ = make_unique<Particle::ParticleEmitter>();
	emitter_->CreateType(make_unique<EmitterSphere>(), gpuParticle_);
	auto& testSphere = emitter_->GetSphereParam()[0];
	testSphere.emit = 1;
	testSphere.count = 8;
	testSphere.frequency = 1.0f;
	testSphere.frequencyTime = 4.0f;
	testSphere.radious = 2.0f;
	auto& testSphere2 = emitter_->GetSphereParam()[1];
	testSphere2.emit = 1;
	testSphere2.count = 8;
	testSphere2.frequency = 1.0f;
	testSphere2.translate.y = -3.0f;
	testSphere2.frequencyTime = 4.0f;
	testSphere2.radious = 2.0f;
}

void GameScene::Update(GameManager* Scene)
{
	Scene;
#ifdef _USE_IMGUI

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

	emitter_->ImGuiUpdate();

#endif // _USE_IMGUI

	player_->Update();

	enemyWalkManager_->Update();

	blockManager_->Update();

	Gravitys();

	Collision();

	gameObjectManager_->Update();

	debugCamera_->Update();

	GameObjectManager::GetInstance();
	LightingManager::AddList(light_);
	PostEffect::GetInstance()->Update();

	emitter_->Update();
	emitter_->Emit(gpuParticle_);
	gpuParticle_->CallBarrier();
	gpuParticle_->Update();
}

void GameScene::PostProcessDraw()
{
	PostEffect::GetInstance()->PreDraw();

	gameObjectManager_->Draw();
	gpuParticle_->Draw();
	emitter_->SpownDraw();
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
