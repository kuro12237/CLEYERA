#include "Player.h"

void Player::Initialize()
{
	SetName("Player");
	SetObjectData(this->transform_);
	this->isExtrusion_ = true;


}

void Player::Update()
{

	if (ImGui::Button("b"))
	{
		velocity_ = {};
		transform_.translate = { 0.0f,4.0f,0.0f };
	}

	//“–‚½‚è”»’è
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
			velocity_ = {};
		}
	}

	transform_.translate.x += extrusion_.x;
	transform_.translate.y += extrusion_.y;
}

void Player::Jamp()
{

	velocity_.y = 0.25f;

}
