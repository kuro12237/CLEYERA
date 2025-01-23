#include "PlayerManager.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerManager::Initialize()
{
	//mainBody
	playerCore_ = make_shared<Player>();
	objDataList_.push_back(playerCore_);

	//reticle
	reticle_ = make_shared<PlayerReticle>();
	objDataList_.push_back(reticle_);

	//Gun
	gun_ = make_shared<PlayerGun>();
	objDataList_.push_back(gun_);

	//Camera
	camera_ = make_shared<PlayerCamera>();
	objDataList_.push_back(camera_);
	
	for (auto& it : objDataList_)
	{
		auto obj = it.lock();
		obj->Initialize();
	}
	camera_->SetTarget(playerCore_->INameable::GetName());

	//Hp
	hp_ = make_shared<PlayerHp>();
	hp_->Initialize(kPlayerHp_);

	//commands
	commandHandler_ = make_shared<PlayerCommandHandler>();

	playerCore_->SetPlayerHP(hp_);
	playerCore_->SetReduceHpFunc(std::bind(&PlayerHp::ReduceHp, hp_.get()));


	gameObjectManager_->CameraReset(camera_->GetName());

	//po
	p_ReticleWorldPos_ = &gameObjectManager_->GetObj3dData_ptr(reticle_->GetName())->GetWorldTransform().transform.translate;
	p_GunWorldPos_ = &gameObjectManager_->GetObj3dData_ptr(gun_->GetName())->GetWorldTransform().transform.translate;
	p_CoreWorldPos_ = &gameObjectManager_->GetObj3dData_ptr(playerCore_->INameable::GetName())->GetWorldTransform().transform.translate;
	gameObjectManager_->GetObj3dData(reticle_->GetName())->SetIsDraw(false);

	gun_->SetTarget(*p_ReticleWorldPos_);
	gun_->SetPlayerPos(gameObjectManager_->GetObj3dData_ptr(playerCore_->INameable::GetName())->GetWorldTransform().transform.translate);
	gun_->SetPlayerVelo(playerCore_->GetVelocity());

	
	//ダメージの演出関数をセット
	playerCore_->SetDamageUpdateFunc(std::bind(&PlayerManager::DamegeUpdate, this));
	playerCore_->SetDamageUpdateEndFunc(std::bind(&PlayerManager::DamegeUpdateEnd, this));

	reticle_->SetPlayer(playerCore_);
	gun_->SetPlayer(playerCore_);

	ModelManager::ModelLoadNormalMap();
	bulletModelHandle_ = ModelManager::LoadObjectFile("PlayerNormalBullet");
	bulletManager_ = make_unique<PlayerBulletManager>();
	bulletManager_->Initialize();

	moveParticle_ = make_unique<PlayerMoveParticle>();
	moveParticle_->Initialize();
	moveParticle_->SetPlayerPos(gameObjectManager_->GetObj3dData(playerCore_->INameable::GetName())->GetWorldTransform().transform.translate);

	deadParticle_ = make_unique<PlayerDeadParticle>();
	deadParticle_->Initialize();
	deadParticle_->SetPlayerPos(gameObjectManager_->GetObj3dData(playerCore_->INameable::GetName())->GetWorldTransform().transform.translate);
}

void PlayerManager::ImGuiUpdate()
{
	if (ImGui::TreeNode(playerCore_->INameable::GetName().c_str()))
	{
		playerCore_->ImGuiUpdate();
		reticle_->ImGuiUpdate();
		hp_->ImGuiUpdate();

		bulletManager_->ImGuiUpdate();

		ImGui::Text("PlayerBulletSize::%d", bullets_.size());
		if (ImGui::Button("bulleSpown"))
		{
			PushBullet(gameObjectManager_->GetObj3dData(playerCore_->INameable::GetName())->GetWorldTransform().GetWorldPosition());
		}
		ImGui::TreePop();
	}

	moveParticle_->ImGuiUpdate();

}

void PlayerManager::Update()
{
	RemoveEmptyObjList();

	//ゲームが終わる通知
	if (playerCore_->GetIsGameEnd())
	{
		gameStartFlag_ = false;
	}

	//Commands
	if (gameStartFlag_ && !playerCore_->IsInState<PlayerStateGoalAnimation>())
	{
		//プレイヤーの操作キャラ
		commandHandler_->Handler();
		commandHandler_->CommandsExec(*playerCore_);
	}

	//hpがなくなったら
	if (hp_->GetHp() <= 0 && !playerCore_->IsInState<PlayerStateDeadAnimation>())
	{
		playerCore_->AddState<PlayerStateDeadAnimation>();
	}

	bulletManager_->Update();

	//Bullet
	if (playerCore_->GetIsShoot())
	{
		if (bulletManager_->GetBulletCount() < 5)
		{
			bulletManager_->BulletCountAdd();
			PushBullet(*p_GunWorldPos_);
		}
	}

	hp_->Update();

	for (auto& it : objDataList_)
	{
		if (auto obj = it.lock()) {
			obj->Update();
		}
	}

	//Bullets
	CheckisDeadBullets();

	if (playerCore_->IsInState<PlayerStateWalk>()||playerCore_->IsInState<PlayerStateDash>())
	{
		moveParticle_->SetIsEmit(true);
	}
	else
	{
		moveParticle_->SetIsEmit(false);
	}

	//死んだアニメーションを再生してるとき
	if (playerCore_->IsInState<PlayerStateDeadAnimation>())
	{
		deadParticle_->SetIsEmit(true);
	}
	moveParticle_->Update();
	deadParticle_->Update();

}

void PlayerManager::Draw2d()
{
	reticle_->Draw2d();
}

void PlayerManager::DrawHp()
{
	hp_->Draw2d();

}

void PlayerManager::Draw2dBullet()
{
	bulletManager_->Draw2d();
}

void PlayerManager::DrawParticle()
{
	moveParticle_->Draw();
	deadParticle_->Draw();
}

void PlayerManager::PushBullet(const Math::Vector::Vector3& pos)
{
	//オブジェクトの作成
	shared_ptr<Game3dObjectData> data = make_shared<Game3dObjectData>();
	data->SetObjectType("MESH");
	data->Initialize({}, {}, bulletModelHandle_);

	//弾の拡散範囲計算
	//xMin/yMax
	const Math::Vector::Vector2 spreadRangeMax = { -0.5f,0.5f };

	//velocityの計算
	Math::Vector::Vector3 velocity = Math::Vector::Subtruct(*p_ReticleWorldPos_, *p_GunWorldPos_);
	velocity.x += RandomGenerator::GetFloat(spreadRangeMax.x, spreadRangeMax.y);
	velocity.y += RandomGenerator::GetFloat(spreadRangeMax.x, spreadRangeMax.y);
	velocity = Math::Vector::Normalize(velocity);

	shared_ptr<PlayerBullet> b = make_shared<PlayerBullet>();
	string name = "PlayerBullet";
	b->SetVelocity(velocity);
	b->SetSpownPos(pos);

	//使っていない弾の配列がある時再利用
	if (!deadBulletIndex_.empty())
	{
		uint32_t newBulletIndex = deadBulletIndex_.front();
		string name_num = name + to_string(newBulletIndex);
		data->SetObjName(name_num);
		GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
		b->SetName(name_num);
		b->Initialize();
		objDataList_.push_back(b);
		bullets_[newBulletIndex] = move(b);
		deadBulletIndex_.pop();
	}
	else
	{
		//新しいindexをとリ弾にセット
		int size = int(bullets_.size());
		string name_num = name + to_string(size);
		data->SetObjName(name_num);
		GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
		b->SetName(name_num);
		b->Initialize();
		objDataList_.push_back(b);
		bullets_.push_back(move(b));
	}
}

void PlayerManager::CheckisDeadBullets()
{
	for (size_t index = 0; index < bullets_.size(); ++index)
	{
		if (!bullets_[index])
		{
			continue;
		}
		if (bullets_[index]->GetIsDeadFlag())
		{
			bullets_[index]->INameable::GetName();
			deadBulletIndex_.push(uint32_t(index));
			GameObjectManager::GetInstance()->ClearObj3dData(bullets_[index]->INameable::GetName());
			bullets_[index].reset();
		}
	}
}

void PlayerManager::DamegeUpdate()
{
	const float vinatteScale = 64.0f;
	const float vinateFactorSpeed = 1.0f / 120.0f;
	const Math::Vector::Vector3 color = { 1.0f,0.0f,0.0f };
	//ビネットをかける
	postEffect_->SetSelectPostEffect(VIGNETTE, true);
	postEffect_->SetVignetteScale(vinatteScale);
	postEffect_->SetVignetteFactor(vinatteFactor_);
	postEffect_->SetVignetteColor(color);

	vinatteFactor_ -= vinateFactorSpeed;

}

void PlayerManager::DamegeUpdateEnd()
{

	postEffect_->SetSelectPostEffect(VIGNETTE, false);
	postEffect_->SetVignetteFactor(0.0f);
	vinatteFactor_ = vinatteFactorMax_;
}


