#include "PlayerGun.h"

void PlayerGun::Initlalize()
{
	//model設定
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObjectDesc_.useLight = true;
	gameObject_->SetDesc(gameObjectDesc_);
	modelHandle_ = ModelManager::LoadObjectFile("PlayerGun");
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();

	//状態
	state_ = make_unique<PlayerGunStandState>();
	state_->Initialize();
}

void PlayerGun::Update()
{

	//弾消し
	bullets_.remove_if([](shared_ptr<PlayerGunBullet> b) {
		if (b->GetIsDeadFlag()) {
			b.reset();
			return true;
		}
		return false;
		});

	for (shared_ptr<PlayerGunBullet> b : bullets_)
	{
		b->Update();
	}

	if (state_)
	{
		state_->Update(this);
	}

	worldTransform_.UpdateMatrix();
}

void PlayerGun::Animation()
{
}

void PlayerGun::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_, camera);

	for (shared_ptr<PlayerGunBullet> b : bullets_)
	{
		b->Draw(camera);
	}
}

void PlayerGun::ImGuiUpdate()
{
	if (ImGui::TreeNode("Gun"))
	{
		ImGui::TreePop();
	}
}

void PlayerGun::Attack()
{
	if (state_->GetstateNo() == ATTACK || state_->GetstateNo() == RELOAD)
	{
		return;
	}
	ChangeState(ATTACK);
}

void PlayerGun::ChangeState(PLAYERGUNSTATE state)
{
	switch (state)
	{
	case STAND:
		state_ = make_unique<PlayerGunStandState>();
		break;
	case RELOAD:
		state_ = make_unique<PlayerGunReloadState>();
		break;
	case ATTACK:
		state_ = make_unique<PlayerGunAttackState>();
		break;
	default:
		break;
	}
	state_->Initialize();
}

bool PlayerGun::BulletPushBack(shared_ptr<PlayerGunBullet> b)
{
	bulletCount_++;
	if (bulletCount_ <= bulletCountMax_)
	{
		bullets_.push_back(b);
		return true;
	}
	else
	{
		ChangeState(RELOAD);
		return false;
	}
}