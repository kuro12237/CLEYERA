#include "Player.h"

void Player::Initialize()
{
	gameObjectInstance_ = GameObjectManager::GetInstance();
	name_ = "Player";

	//�����o��
	this->isExtrusion_ = true;
	//��Ԉُ�̃X�e�[�g
	state_ = make_unique<PlayerStateNone>();
	state_->Initialize(this);
	//id�ݒ�
	id_ = kPlayerId;
	//�����蔻��
	SetObjectData(gameObjectInstance_->GetObj3dData_ptr(name_)->GetWorldTransform().transform);
	aabb_ = gameObjectInstance_->GetObj3dData(name_)->GetAABB();
	//�X�P�[���l�Z�b�g
	auto& transform = gameObjectInstance_->GetObj3dData(name_)->GetWorldTransform().transform;
	const float kScale = 0.4f;
	transform.scale = { kScale,kScale,kScale };

	string filePath = gameObjectInstance_->GetObj3dData(name_)->GetMOdelFilePath();
	AnimationManager::GetInstance()->LoadAnimation(filePath);
	walkAnimationData_ = AnimationManager::GetInstance()->GetData(filePath);

	auto* emitters = CharacterMoveParticle::GetInstance()->GetEmitter();

	uint32_t index = 0;
	for (auto& emitter : emitters->GetControlParam())
	{
		if (!emitter.useFlag_)
		{
			emitter.useFlag_ = true;
			particleMoveIndex_ = index;
			auto& param = emitters->GetEmitParam()[particleMoveIndex_];
			param.count = 4;
			emitter.frequencyTime = 0.18f;
			param.velocityMax = { 0.0f,0.01f,0.0f };
			param.velocityMin = { 0.0f,0.01f,0.0f };
			param.sizeMax = { 0.1f,0.5f,0.1f };
			param.sizeMin = { -0.1f,-0.1f,-0.1f };
			param.colorDecayMax.w = 0.05f;
			param.colorDecayMin.w = 0.025f;
			break;
		}
		index++;
	}
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
	string filePath = gameObjectInstance_->GetObj3dData(name_)->GetMOdelFilePath();

	walkAnimationFlame_ = std::fmod(walkAnimationFlame_, walkAnimationData_.duration);
	gameObjectInstance_->GetObj3dData(name_)->GetGameObject()->SkeletonUpdate(filePath, walkAnimationFlame_);

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
	auto& transform = gameObjectInstance_->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.translate = Math::Vector::Add(transform.translate, velocity_);

	//�p�[�e�B�N���̔z�u�ʒu
	auto& moveEmitParam = CharacterMoveParticle::GetInstance()->GetEmitter()->GetEmitParam()[particleMoveIndex_];
	moveEmitParam.translate = transform.translate;
    float particleOffsetY = aabb_.min.y / 2.0f + aabb_.min.y / 4.0f;
	moveEmitParam.translate.y += particleOffsetY;
}

void Player::OnCollision(ICollider* c)
{
	if (kOnlyCollideWithBlocksid)
	{
		return;
	}

	if (!isDamage_)
	{
		if (c->GetId() == kEnemyWalkId)
		{
			ChangeState(make_unique<PlayerStateRock>());
			//Input::VibrateController(65000, 65000, 20.0f);
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
	//�Ή��̂Ƃ��͒ʂ��Ȃ�
	if (isRockState_)
	{
		return;
	}

	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();
	auto& rotate = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform.rotate;

	{//�ړ�����
		ControlDeadZone(Ljoy);
		velocity_.x = Ljoy.x * speed;
	}

	{//��]����
		//�E
		const float degrees = 90.0f;
		float radian = 0.0f;
		if (velocity_.x > 0.0f)
		{
			radian = Math::Vector::degreesToRadians(degrees);
		}
		//��
		if (velocity_.x < 0.0f)
		{
			radian = Math::Vector::degreesToRadians(-degrees);
		}
		rotate.y = radian;
	}

	//�A�j���[�V����
	walkAnimationFlame_ += (1.0f / 30.0f) * fabsf(Ljoy.x);

	//�p�[�e�B�N��
	CharacterMoveParticle::GetInstance()->Emit();

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
	//�r�l�b�g��������
	PostEffect* instance = PostEffect::GetInstance();
	instance->SetSelectPostEffect(VIGNETTE, true);
	const float vinatteScale = 64.0f;
	instance->SetVignetteScale(vinatteScale);
	instance->SetVignetteFactor(vinatteFactor_);

	const float vinateFactorSpeed = 0.007f;
	damegeCoolTimer_ += DeltaTimer(damegeFlame_);
	vinatteFactor_ -= vinateFactorSpeed;

	if (damegeCoolTimer_ >= damageCoolTimerMax_)
	{
		instance->SetSelectPostEffect(VIGNETTE, false);
		instance->SetVignetteFactor(0.0f);
		vinatteFactor_ = 1.0f;
		damegeCoolTimer_ = 0;
		isDamage_ = false;
	}
}

void Player::ShootCoolTimer()
{

}

void Player::ControlDeadZone(Math::Vector::Vector2& v)
{
	const float deadNum = 0.1f;
	if (v.x >= -deadNum && v.x <= deadNum)
	{
		v.x = {};
	}
	if (v.y >= -deadNum && v.y <= deadNum)
	{
		v.y = {};
	}
}
