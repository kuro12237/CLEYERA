#include "Player.h"

void Player::Initialize()
{
	worldTransform_.Initialize();

	modelHandle_ = ModelManager::LoadObjectFile("TestPlayer");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);

	worldTransform_.translate.y = 4.0f;
	worldTransform_.translate.x = 4.0f;

	aabb_.min = { -0.5f,-0.5f,-0.5f };
	aabb_.max = { 0.5f,0.5f,0.5f };
	
	SetAABB(aabb_);
	SetAttbute(kPlayerAttbute);
	SetMask(kPlayerMask);
	IBoxCollider::SetVelocity(velocity_);
	IBoxCollider::SetId(kPlayerId);
	IBoxCollider::SetWorldTransform(worldTransform_);

	IGravity::SetVelocity(velocity_);

	GlobalVariables::GetInstance()->CreateGroup("Player");

	worldTransform_.scale = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "scale");
	GameStartPos_ = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "startPos");
	worldTransform_.translate = GameStartPos_;
}

void Player::Update()
{
	GlobalVariables::GetInstance()->AddItem("Player", "scale", worldTransform_.scale);
	GlobalVariables::GetInstance()->AddItem("Player", "startPos", GameStartPos_);

	worldTransform_.scale = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "scale");
	GameStartPos_ = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "startPos");

	Move();


	ClearFlag();
}

void Player::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_, camera);
}

void Player::ImGuiUpdate()
{
	if (ImGui::TreeNode("Player"))
	{
		bool f = GetTopFlag();
		ImGui::Checkbox("T", &f);

		f = GetBottomFlag();
		ImGui::Checkbox("B", &f);

		f = GetRightFlag();
		ImGui::Checkbox("R", &f);

		f = GetLeftFlag();
		ImGui::Checkbox("L", &f);

		ImGui::TreePop();
	}

	if (ImGui::Button("Reset"))
	{

		worldTransform_.scale = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "scale");
		GameStartPos_ = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "startPos");
		worldTransform_.translate = GameStartPos_;
		worldTransform_.UpdateEularQuaternionMatrix();
	}

}

Math::Vector::Vector3 Player::GetWorldPosition()
{
	return worldTransform_.GetWorldPosition();
}

void Player::OnCollision(IBoxCollider* collider)
{
	collider;
	Math::Vector::Vector2 extrusion = this->GetExtrusionXY();
	worldTransform_.translate.x += extrusion.x;
	worldTransform_.translate.y += extrusion.y;
	worldTransform_.UpdateEularMatrix();

	if (collider->GetId() == kLuggageId)
	{
		//float x = collider->GetVelocity().x;
		//worldTransform_.translate.x += x;
		worldTransform_.UpdateEularMatrix();

	}
	if (GetBottomFlag() && velocity_.y <= 0.0f)
	{
		isJamp_ = false;
		velocity_ = {};
	}
	if (GetTopFlag())
	{
		velocity_ = {};
	}
}

void Player::GravityExc(const Math::Vector::Vector2 &g)
{
	velocity_ = g;
	worldTransform_.translate.y += velocity_.y;
	worldTransform_.UpdateEularMatrix();

}



void Player::Move()
{
	Math::Vector::Vector2 Ljoy = Input::GetJoyLStickPos();
	if (Ljoy.x >= -0.1f && Ljoy.x <= 0.1f)
	{
		Ljoy.x = {};
	}
	if (Ljoy.y >= -0.1f && Ljoy.y <= 0.1f)
	{
		Ljoy.y = {};
	}
	//float Length = VectorTransform::Length(Vector3(Ljoy.x, Ljoy.y, 0.0f));
	//if (Length <= 0.1f)
	//{
	//	Ljoy = {};
	//}

	const float Speed = 0.1f;
	
	velocity_.x = Ljoy.x * Speed;

	worldTransform_.translate.x +=velocity_.x;
	//worldTransform_.translate.y += AddPos.y;
}

void Player::Jamp()
{
	if (!isJamp_ && velocity_.y == 0.0f)
	{
		velocity_.y = 0.25f;
		isJamp_ = true;
	}
}
