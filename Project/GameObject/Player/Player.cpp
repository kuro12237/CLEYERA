#include "Player.h"

void Player::Initialize()
{
	worldTransform_.Initialize();

	modelHandle_ = ModelManager::LoadObjectFile("Player");
	modelHandle_ = ModelManager::LoadGltfFile("walk",true);
	AnimationManager::GetInstance()->LoadAnimation("walk");
	animationData_ = AnimationManager::GetInstance()->GetData("walk");

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	game3dObjectdesc_.useLight = true;
	gameObject_->SetName("player");
	gameObject_->SetDesc(game3dObjectdesc_);
	gameObject_->SetModel(modelHandle_);
	gameObject_->CreateSkinningParameter();

	worldTransform_.UpdateMatrix();

	reticle_ = make_unique<PlayerReticle>();
	reticle_->Initialize();
	reticle_->SetParent(worldTransform_);
	reticle_->Update();

	gun_ = make_unique<PlayerGun>();
	gun_->Initlalize();
	gun_->SetParent(worldTransform_);

	hp_ = make_unique<PlayerHp>();
	hp_->Initialize();

	hpCount_ = &hp_->GetHp();

	aabb_.min = { -0.5f,-0.5f,-0.5f };
	aabb_.max = { 0.5f,0.5f,0.5f };
	
	IBoxCollider::SetAABB(aabb_);
	IBoxCollider::SetAttbute(kPlayerAttbute);
	IBoxCollider::SetMask(kPlayerMask);
	IBoxCollider::SetVelocity(velocity_);
	IBoxCollider::SetId(kPlayerId);
	IBoxCollider::SetWorldTransform(worldTransform_);

	IGravity::SetVelocity(velocity_);

	GlobalVariables::GetInstance()->CreateGroup("Player");

	worldTransform_.scale = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "scale");
	GameStartPos_ = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "startPos");
	worldTransform_.translate = GameStartPos_;

	state_ = make_unique<PlayerNormaState>();
	state_->Initialize();

}

void Player::Update()
{
	GlobalVariables::GetInstance()->AddItem("Player", "scale", worldTransform_.scale);
	GlobalVariables::GetInstance()->AddItem("Player", "startPos", GameStartPos_);

	worldTransform_.scale = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "scale");
	GameStartPos_ = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "startPos");

	isHit_ = false;

	if (state_)
	{
		state_->Update(this);
	}

	flame_ += 1.0f / 30.0f;
	flame_ = std::fmod(flame_, animationData_.duration);
	gameObject_->SkeletonUpdate("walk", flame_);
	gameObject_->SkinningUpdate();


	reticle_->Update();
	gun_->ReticlePos(reticle_->GetPos());
	gun_->Update();

	hp_->Update();

	ClearFlag();
}

void Player::Draw(const CameraData& camera)
{
	reticle_->Draw3d(camera);
	gun_->Draw(camera);
	gameObject_->Draw(worldTransform_, camera);

}

void Player::Draw2d(const CameraData& camera)
{
	hp_->Draw2d(camera);
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

		if (ImGui::Button("Reset"))
		{

			worldTransform_.scale = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "scale");
			GameStartPos_ = GlobalVariables::GetInstance()->GetValue<Math::Vector::Vector3>("Player", "startPos");
			worldTransform_.translate = GameStartPos_;
			worldTransform_.UpdateEularMatrix();
		}

		//ImGui::Text("%f %f %f", reticle_->GetPos().x, reticle_->GetPos().y, reticle_->GetPos().z);
		ImGui::Separator();
		gun_->ImGuiUpdate();
		ImGui::Separator();
		hp_->ImGuiUpdate();
		ImGui::TreePop();
	}
}

Math::Vector::Vector3 Player::GetWorldPosition()
{
	return worldTransform_.GetWorldPosition();
}

Math::Vector::Vector3 Player::GetSize()
{
	return Math::Vector::Vector3(0.5f,0.5f,0.5f);
}

Math::Vector::Vector3 Player::GetRotate()
{
	return worldTransform_.rotation;
}

void Player::OnBlockCollision(IBoxCollider* collider)
{
	collider;
	Math::Vector::Vector2 extrusion = this->GetExtrusionXY();
	worldTransform_.translate.x += extrusion.x;
	worldTransform_.translate.y += extrusion.y;
	worldTransform_.UpdateMatrix();
	
	reticle_->WorldTransformUpdate();
	gun_->WorldTransformUpdate();

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

void Player::OnCollision(uint32_t id)
{
	isHit_ = true;

	if (id == kStoneItem)
	{
		ChangeState(make_unique<PlayerStoneState>());
		return;
	}

}

void Player::GravityExc(const Math::Vector::Vector2& g)
{
	velocity_ = g;
	worldTransform_.translate.y += velocity_.y;
	worldTransform_.UpdateMatrix();;

	reticle_->WorldTransformUpdate();
	gun_->WorldTransformUpdate();
}

void Player::ChangeState(unique_ptr<IPlayerState> state)
{
	state_ = move(state);
	state_->Initialize();
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

	const float Speed = 0.1f;

	velocity_.x = Ljoy.x * Speed;
	worldTransform_.translate.x += velocity_.x;

	worldTransform_.UpdateEularMatrix();
}

void Player::Jamp()
{
	if (behavior_ == Normal)
	{
		if (!isJamp_ && velocity_.y == 0.0f)
		{
			AudioManager::GetInstance()->AudioPlayMp3("Resources/Sounds/Jump.mp3", 1.0f);
			velocity_.y = 0.25f;
			isJamp_ = true;
		}
	}
}

void Player::GunAttack()
{
	if (behavior_ == Normal)
	{
		gun_->Attack();
	}
}