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
}

void PlayerManager::ImGuiUpdate()
{
	playerCore_->ImGuiUpdate();
	reticle_->ImGuiUpdate();
	gun_->Update();

	ImGui::Text("PlayerBulletSize::%d", bullets_.size());
	if (ImGui::Button("bulleSpown"))
	{
		GameObjectManager* instance = GameObjectManager::GetInstance();
		PushBullet(instance->GetObj3dData(playerCore_->GetName()).worldTransform.GetWorldPosition());
	}
}

void PlayerManager::Update()
{
	GameObjectManager* instance = GameObjectManager::GetInstance();
	reticleWorldPos = instance->GetObj3dData(reticle_->GetName()).worldTransform.GetWorldPosition();
	playerWorldPos = instance->GetObj3dData(playerCore_->GetName()).worldTransform.GetWorldPosition();

	gun_->SetTarget(reticleWorldPos);

	reticleCommandHandler_->Handler();
	reticleCommandHandler_->Exec(*reticle_);
	reticle_->Update();

	commandHandler_->Handler();
	commandHandler_->CommandCoreExec(*playerCore_);
	if (playerCore_->GetIsShoot())
	{
		PushBullet(playerWorldPos);
	}

	playerCore_->Update();

	CheckisDeadBullets();

	for (shared_ptr<PlayerBullet>& b : bullets_)
	{
		if (b)
		{
			b->Update();
		}
	}
}

void PlayerManager::PushBullet(Math::Vector::Vector3 pos)
{
	//�I�u�W�F�N�g�̍쐬
	Game3dObjectData data;
	data.gameObject = make_unique<Game3dObject>();
	data.gameObject->Create(make_unique<Phong3dPipline>());
	data.gameObject->SetModel("DfCube");
	data.gameObject->SetDesc(data.objectDesc);
	data.worldTransform.Initialize();
	data.worldTransform.translate = pos;

	shared_ptr<PlayerBullet> b = make_shared<PlayerBullet>();
	//velocity�̌v�Z
	Math::Vector::Vector3 velocity = Math::Vector::Subtruct(reticleWorldPos,playerWorldPos);
	velocity = Math::Vector::Normalize(velocity);

	b->SetVelocity(velocity);
	b->SetSpownPos(pos);
	b->Initialize();
	//�g���Ă��Ȃ��e�̔z�񂪂��鎞�ė��p
	if (!deadBulletIndex_.empty())
	{
		uint32_t newBulletIndex = deadBulletIndex_.front();
		string name = b->GetName() + to_string(newBulletIndex);
		b->SetName(name);

		GameObjectManager::GetInstance()->PushObj3dData(data, b->GetName());
		bullets_[newBulletIndex] = move(b);
		deadBulletIndex_.pop();
	}
	else
	{
		//�V����index���ƃ��e�ɃZ�b�g
		int size = int(bullets_.size());
		string name = b->GetName() + to_string(size);
		b->SetName(name);
		GameObjectManager::GetInstance()->PushObj3dData(data, b->GetName());
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
