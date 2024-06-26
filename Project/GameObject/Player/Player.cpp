#include "Player.h"

void Player::Initialize()
{
	SetName("Player");
	SetObjectData(this->transform_);
	this->isExtrusion_ = true;

	state_ = make_unique<PlayerStateNone>();
	state_->Initialize(this);

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
		ImGui::TreePop();
	}
}

void Player::Update()
{

	if (state_)
	{
		state_->Update(this);
	}


	if (velocity_.y <= 0.0f)
	{
		isJamp_ = true;
	}

	transform_.translate = Math::Vector::Add(transform_.translate, velocity_);
}

void Player::OnCollision(ICollider* c)
{
	c;

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

void Player::ChangeState(unique_ptr<IPlayerState> newState)
{
	state_.release();
	state_ = move(newState);
	state_->Initialize(this);
}

void Player::Jamp()
{
	if (!isJamp_)
	{
		isJamp_ = true;
		velocity_.y = 0.25f;
	}
}

void Player::Move()
{
	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();

	const float Speed = 0.1f;
	velocity_.x = Ljoy.x * Speed;

}
