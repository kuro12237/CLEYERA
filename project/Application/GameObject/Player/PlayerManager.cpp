#include "PlayerManager.h"

void PlayerManager::GetData(GameObjectManager* data)
{
	playerCore_ = make_shared<Player>();
	playerCore_->Initialize();
	playerCore_->GetData(data);

	commandHandler_ = make_unique<PlayerCommandHandler>();
	reticleCommandHandler_ = make_unique<PlayerReticleCommandHandler>();

	reticle_ = make_unique<PlayerReticle>();
	reticle_->Initialize();

	gun_ = make_unique<PlayerGun>();
	gun_->Initialize();

	camera_ = make_unique<PlayerCamera>();
	camera_->SetTargetName(playerCore_->GetName());
	camera_->Initialize();

	data->CameraReset(camera_->GetName());
}

void PlayerManager::ImGuiUpdate()
{
	if (ImGui::TreeNode(playerCore_->GetName().c_str()))
	{
		playerCore_->ImGuiUpdate();
		reticle_->ImGuiUpdate();

		ImGui::Text("PlayerBulletSize::%d", bullets_.size());
		if (ImGui::Button("bulleSpown"))
		{
			GameObjectManager* instance = GameObjectManager::GetInstance();
			PushBullet(instance->GetObj3dData(playerCore_->GetName())->GetWorldTransform().GetWorldPosition());
		}
		ImGui::TreePop();
	}
}

void PlayerManager::Update()
{
	GameObjectManager* instance = GameObjectManager::GetInstance();
	reticleWorldPos = instance->GetObj3dData(reticle_->GetName())->GetWorldTransform().GetWorldPosition();
	playerWorldPos = instance->GetObj3dData(playerCore_->GetName())->GetWorldTransform().GetWorldPosition();

	//ゲームが終わる通知
	if (playerCore_->GetIsGameEnd())
	{
		gameStartFlag_ = false;
	}

	if (gameStartFlag_ && !playerCore_->GetIsGoal())
	{
		commandHandler_->Handler();
		commandHandler_->CommandsExec(*playerCore_);
	}

	if (playerCore_->GetIsShoot())
	{
		PushBullet(playerWorldPos);
	}

	playerCore_->Update();

	gun_->SetTarget(reticleWorldPos);
	gun_->Update();
	reticleCommandHandler_->Handler();
	reticleCommandHandler_->Exec(*reticle_);
	reticle_->Update();

	camera_->Update();

	CheckisDeadBullets();

	for (shared_ptr<PlayerBullet>& b : bullets_)
	{
		if (b)
		{
			b->Update();
		}
	}
}

void PlayerManager::Draw2d()
{
	reticle_->Draw2d();
}

void PlayerManager::PushBullet(Math::Vector::Vector3 pos)
{

	ModelManager::ModelLoadNormalMap();
	uint32_t modelHandle = ModelManager::LoadObjectFile("PlayerNormalBullet");
	//オブジェクトの作成
	shared_ptr<Game3dObjectData> data;
	data = make_shared<Game3dObjectData>();
	TransformEular transform;
	transform.scale = { 1.0f,1.0f,1.0f };
	transform.translate = pos;
	data->SetObjectType("MESH");
	data->Initialize(transform, {}, modelHandle);

	shared_ptr<PlayerBullet> b = make_shared<PlayerBullet>();
	string name = "PlayerBullet";

	//弾の拡散範囲計算
	//xMin/yMax
	const Math::Vector::Vector2 spreadRangeMax = { -0.5f,0.5f };
	Math::Vector::Vector2 spreadRange = {
		RandomGenerator::GetFloat(spreadRangeMax.x,spreadRangeMax.y),
		RandomGenerator::GetFloat(spreadRangeMax.x,spreadRangeMax.y)
	};

	//velocityの計算
	Math::Vector::Vector3 velocity = Math::Vector::Subtruct(reticleWorldPos, playerWorldPos);
	velocity.x += spreadRange.x;
	velocity.y += spreadRange.y;
	velocity = Math::Vector::Normalize(velocity);

	b->SetPlayerSpeed(playerCore_->GetVelocity());
	b->SetVelocity(velocity);
	b->SetSpownPos(pos);

	//使っていない弾の配列がある時再利用
	if (!deadBulletIndex_.empty())
	{
		uint32_t newBulletIndex = deadBulletIndex_.front();
		string name_num = name + to_string(newBulletIndex);
		data->SetObjName(name_num);
		GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
		b->Initialize(name_num);
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
		b->Initialize(name_num);
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
			bullets_[index]->GetName();
			deadBulletIndex_.push(uint32_t(index));
			GameObjectManager::GetInstance()->ClearObj3dData(bullets_[index]->GetName());
			bullets_[index].reset();
		}
	}
}
