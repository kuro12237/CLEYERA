#include "GameScene.h"

using namespace Engine::Manager;

void GameScene::Initialize()
{

	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/GameScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/GameScene/");

	//levelData�̓ǂݍ���
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->MoveData(levelData.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();

	light_.radious = 1024.0f;
	light_.position.y = 128.0f;
	light_.position.z = -64.0f;
	light_.decay = 0.1f;


	//Particle������
	ParticlesInitialize();

	GoalParticle::GetInstance()->Clear();

	player_ = make_unique<PlayerManager>();
	player_->Initialize();
	
	enemyWalkManager_ = make_unique<EnemyWalkManager>();
	enemyWalkManager_->Initialize();

	blockManager_ = make_shared<BlockManager>();
	blockManager_->Initialize();

	gameCollisionManager_ = make_unique<BoxCollisionManager>();
	gravityManager_ = make_unique<GravityManager>();

	goal_ = make_unique<Goal>();
	goal_->Initialize(kGoalId, 0);

	warpManager_ = make_unique<WarpManager>();
	warpManager_->Initialize();

	//2dObj
	startAnimation_ = make_unique<StartAnimation>();
	startAnimation_->Initialize();

	endAnimation_ = make_unique<EndAnimation>();
	endAnimation_->Initialize();

	gameUi_ = make_unique<GameSceneUI>();
	gameUi_->Initialize();

	//�X�V
	gameObjectManager_->Update();
	LightingManager::AddList(light_);

	//�Q�[���I���̂Ȃ�
	isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();


	this->SetFlont2dSpriteDrawFunc(std::bind(&GameScene::Flont2dSpriteDraw, this));
	this->SetPostEffectDrawFunc(std::bind(&GameScene::PostProcessDraw, this));

}

void GameScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	ImGuiUpdate();

#endif // _USE_IMGUI

	ChangeSceneAnimation::GetInstance()->Update();

	//�V�[���ؑւ��I�������
	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
		startAnimation_->SetIsCountStart(true);
	}

	//�J�E���g�_�E�����I�������
	if (startAnimation_->GetIsGameStartFlag())
	{
		enemyWalkManager_->SetIsStartFlag(true);
		player_->SetStartFlag(true);
	}

	startAnimation_->Update();
	endAnimation_->Update();

	//
	//�Q�[���J�n��
	//

	gameUi_->Update();

	player_->Update();

	enemyWalkManager_->Update();

	blockManager_->Update();

	goal_->Update();

	warpManager_->Update();

	Gravitys();

	Collision();

	gameObjectManager_->Update();

	ParticlesUpdate();

	LightingManager::AddList(light_);
	PostEffect::GetInstance()->Update();

	//�S�[�������Ƃ�player�̃A�j���[�V�������I�������
	if (*isGameEnd_)
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		enemyWalkManager_->SetIsStartFlag(false);
		player_->SetStartFlag(false);
	}


	///�v���C���[�����񂾂Ƃ�
	if (player_->GetPlayerCore()->GetIsDeadAnimationComplite())
	{
		//�V�[���؂�ւ��J�n
		ChangeSceneAnimation::GetInstance()->ChangeStart();
		//�r�l�b�g���o�Ă��������
		PostEffect::GetInstance()->SetSelectPostEffect(VIGNETTE, false);

		endAnimation_->SetIsCountStart(true);
		//object�ݒ�
		enemyWalkManager_->SetIsStartFlag(false);
		player_->SetStartFlag(false);
		player_->GetPlayerCore()->SetIsGameEnd(true);
	}

	//�I���̃A�j���[�V�������I�������
	if (endAnimation_->GetCompleteFlag())
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
	}

	if (player_->GetHp()->GetHp() <= 0 && ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeScene(make_unique<GameOverScene>());
		return;
	}
	//�ؑ�
	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeScene(make_unique<GameClearScene>());
		return;
	}

	gameCollisionManager_->End();

}

void GameScene::PostProcessDraw()
{

	gameObjectManager_->Draw();

	ParticlesDraw();

}

void GameScene::Flont2dSpriteDraw()
{
	
	if (startAnimation_->GetIsGameStartFlag())
	{
		player_->Draw2d();
		player_->DrawHp();
		gameUi_->Draw2d();
	}
	startAnimation_->Draw2d();
	ChangeSceneAnimation::GetInstance()->Draw();
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

	ParticleImGuiUpdate();
	ChangeSceneAnimation::GetInstance()->ImGuiUpdate();

	this->gameUi_->ImGuiUpdate();


}

void GameScene::Collision()
{
	if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>())
	{
		gameCollisionManager_->ListPushback(player_->GetPlayerCore(), player_->GetPlayerCore());
	}
	for (size_t index = 0; index < player_->GetBullet().size(); index++)
	{
		if (player_->GetBullet()[index]) {
			gameCollisionManager_->ListPushback(player_->GetBullet()[index].get(), player_->GetBullet()[index].get());
		}
	}

	for (shared_ptr<EnemyWalk>& e : enemyWalkManager_->GetData())
	{
		if (e)
		{
			gameCollisionManager_->ListPushback(e.get(), e.get());
		}
	}

	for (shared_ptr<Block> b : blockManager_->GetBlocks())
	{
		gameCollisionManager_->ListPushback(b.get(), b.get());
	}


	gameCollisionManager_->ListPushback(goal_.get(), goal_.get());

	for (auto& warp : warpManager_->GetWarps())
	{
		gameCollisionManager_->ListPushback(warp->GetWarpGate(), warp->GetWarpGate());
	}

	gameCollisionManager_->CheckAllCollisoin();

}

void GameScene::Gravitys()
{
	gravityManager_->ClearList();

	if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>())
	{
		if (player_->GetPlayerCore()->GetIsUseGravityFlag())
		{
			gravityManager_->PushList(player_->GetPlayerCore());
		}
	}
	for (shared_ptr<EnemyWalk>& e : enemyWalkManager_->GetData())
	{
		if (e)
		{
			gravityManager_->PushList(e.get());
		}
	}
	gravityManager_->CheckGravity();
}

void GameScene::PlayUpdate()
{
}

void GameScene::ParticlesInitialize()
{
	characterDeadParticle_ = CharacterDeadParticle::GetInstance();
	characterDeadParticle_->Initialize();

	characterMoveParticle_ = CharacterMoveParticle::GetInstance();
	characterMoveParticle_->Initialize();
}

void GameScene::ParticlesUpdate()
{
	characterDeadParticle_->Update();
	characterMoveParticle_->Update();
	GoalParticle::GetInstance()->Update();

}

void GameScene::ParticlesDraw()
{
	warpManager_->DebugDraw();


	GoalParticle::GetInstance()->Draw();
	characterDeadParticle_->Draw();
	characterMoveParticle_->Draw();
	player_->DrawParticle();
}

void GameScene::ParticleImGuiUpdate()
{
	if (ImGui::TreeNode("Particles"))
	{
		GoalParticle::GetInstance()->ImGuiUpdate();
		characterDeadParticle_->ImGuiUpdate();
		characterMoveParticle_->ImGuiUpdate();
		ImGui::TreePop();
	}
}
