#include "Player.h"

void Player::Initialize()
{
	SetName("Player");
	SetObjectData(this->transform_);

	this->isExtrusion_ = true;

	state_ = make_unique<PlayerStateNone>();
	state_->Initialize(this);

	id_ = kPlayerId;

	aabb_ = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetAABB();
}

void Player::ImGuiUpdate()
{
	if (ImGui::TreeNode(name_.c_str()))
	{
		if (ImGui::TreeNode("transform"))
		{
			ImGui::DragFloat3("s", &transform_.scale.x, -0.1f, 0.1f);
			ImGui::DragFloat3("r", &transform_.rotate.x, -0.1f, 0.1f);
			ImGui::DragFloat3("t", &transform_.translate.x, -0.1f, 0.1f);

			ImGui::TreePop();
		}
		if (ImGui::Button("Reset"))
		{
			velocity_ = {};
			transform_.translate = { 0.0f,4.0f,0.0f };
		}

		ImGui::DragFloat3("min", &aabb_.min.x, 0.1f);
		ImGui::DragFloat3("max", &aabb_.max.x, 0.1f);
		ImGui::TreePop();
	}
}

void Player::Update()
{

	//velocity_ = {};
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
	transform_.translate = Math::Vector::Add(transform_.translate, velocity_);
}

void Player::OnCollision(ICollider* c)
{
	if (!isDamage_)
	{
		if (c->GetId() == kEnemyWalkId)
		{
			ChangeState(make_unique<PlayerStateRock>());

			isDamage_ = true;
		}
	}

	if (c->GetId() == kNormalBlock)
	{
		for (auto& hitDirection : hitDirection_)
		{
			if (hitDirection == TOP)
			{
				velocity_ = {};
			}
			if (hitDirection == BOTTOM && velocity_.y <= 0.0f)
			{
				isJamp_ = false;
				velocity_ = {};
			}
		}
		transform_.translate.x += extrusion_.x;
		transform_.translate.y += extrusion_.y;
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
		velocity_.y = 0.25f;
	}
}

void Player::Move()
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

	const float Speed = 0.1f;
	velocity_.x = Ljoy.x * Speed;
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
		isDamage_ = false;
	}

}

void Player::ShootCoolTimer()
{

}
