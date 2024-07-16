#include "Player.h"

void Player::Initialize()
{
	SetName("Player");

	SetObjectData(GameObjectManager::GetInstance()->GetObj3dData_ptr(name_)->GetWorldTransform().transform);

	this->isExtrusion_ = true;

	state_ = make_unique<PlayerStateNone>();
	state_->Initialize(this);

	id_ = kPlayerId;

	aabb_ = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetAABB();
}

void Player::ImGuiUpdate()
{
	string imguiTreeName = name_ + "core";
	if (ImGui::TreeNode(imguiTreeName.c_str()))
	{
		if (ImGui::Button("Reset"))
		{
			velocity_ = {};
		}

		ImGui::DragFloat3("min", &aabb_.min.x, 0.1f);
		ImGui::DragFloat3("max", &aabb_.max.x, 0.1f);
		ImGui::TreePop();
	}
}

void Player::Update()
{
	shootTimerFlame_++;
	if (state_)
	{
		state_->Update(this);
	}

	if (velocity_.y <= 0.0f)
	{
		isJamp_ = true;
	}

	if (isDamage_)
	{
		DamageUpdate();
	}

	isShoot_ = false;
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.translate = Math::Vector::Add(transform.translate, velocity_);
}

void Player::OnCollision(ICollider* c)
{
	if (!isDamage_)
	{
		if (c->GetId() == kEnemyWalkId)
		{
			ChangeState(make_unique<PlayerStateRock>());
			Input::VibrateController(65000, 65000,20.0f);
			isDamage_ = true;
		}
	}

	if (c->GetId() == kNormalBlock)
	{
		for (auto& hitDirection : hitDirection_)
		{
			if (hitDirection == TOP && velocity_.y >= 0.0f)
			{
				velocity_ = {};
			}
			if (hitDirection == BOTTOM && velocity_.y <= 0.0f)
			{
				isJamp_ = false;
				velocity_ = {};
			}
		}
		auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform.translate;
		transform.x += extrusion_.x;
		transform.y += extrusion_.y;
	}

}

void Player::ChangeState(unique_ptr<IPlayerState> newState)
{
	state_.release();
	state_ = move(newState);
	state_->Initialize(this);
}

void Player::Jamp()
{
	if (isRockState_)
	{
		return;
	}
	if (!isJamp_)
	{
		isJamp_ = true;
		const float jampMax = 0.35f;
		velocity_.y = jampMax;
	}
}

void Player::Move(float speed)
{
	if (isRockState_)
	{
		return;
	}

	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();

	if (Ljoy.x >= -0.1f && Ljoy.x <= 0.1f)
	{
		Ljoy.x = {};
	}
	if (Ljoy.y >= -0.1f && Ljoy.y <= 0.1f)
	{
		Ljoy.y = {};

	}

	velocity_.x = Ljoy.x * speed;
}

void Player::Shoot()
{
	if (shootTimerFlame_ >= shootTimerMax_)
	{
		isShoot_ = true;
		shootTimerFlame_ = 0;
	}
}

void Player::DamageUpdate()
{
	PostEffect::GetInstance()->SetSelectPostEffect(VIGNETTE, true);
	PostEffect::GetInstance()->SetVignetteScale(64.0f);
	PostEffect::GetInstance()->SetVignetteFactor(vinatteFactor_);

	damegeCoolTimer_ += DeltaTimer(damegeFlame_);
	vinatteFactor_ -= 0.007f;

	if (damegeCoolTimer_ >= damageCoolTimerMax_)
	{
		PostEffect::GetInstance()->SetSelectPostEffect(VIGNETTE, false);
		PostEffect::GetInstance()->SetVignetteFactor(0.0f);
		vinatteFactor_ = 1.0f;
		damegeCoolTimer_ = 0;
		isDamage_ = false;
	}

}

void Player::ShootCoolTimer()
{

}
