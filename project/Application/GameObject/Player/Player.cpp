#include "Player.h"

void Player::Initialize()
{
	INameable::name_ = "Player";

	//��Ԉُ�̃X�e�[�g
	//id�ݒ�
	id_ = kPlayerId;
	//�����蔻��
	//�����o��
	this->isExtrusion_ = true;
	SetObjectData(gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform);
	aabb_ = gameObjectManager_->GetObj3dData(INameable::name_)->GetAABB();
	attribute_ = CollisionMask::kPlayerAttribute;
	mask_ = CollisionMask::kPlayerMask;

	//�X�P�[���l�Z�b�g
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	const float kScale = 0.4f;
	transform.scale = { kScale,kScale,kScale };
	//�X�^�[�g����̋L�^
	resetPos_ = transform.translate;

	string filePath = gameObjectManager_->GetObj3dData(INameable::name_)->GetModelFilePath();
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
	deadParticle_ = make_unique<PlayerDeadParticle>();
	deadParticle_->Initialize();
}

void Player::ImGuiUpdate()
{
	string imguiTreeName = INameable::name_ + "core";
	if (ImGui::TreeNode(imguiTreeName.c_str()))
	{
		if (ImGui::Button("Reset"))
		{
			velocity_ = {};
		}

		ImGui::DragFloat3("min", &aabb_.min.x, 0.1f);
		ImGui::DragFloat3("max", &aabb_.max.x, 0.1f);

		ImGui::Text("%d", static_cast<int>(states_.size()));

		ImGui::TreePop();
	}
}

void Player::Update()
{
	deadParticle_->Update();

	string filePath = gameObjectManager_->GetObj3dData(INameable::name_)->GetModelFilePath();

	walkAnimationFlame_ = std::fmod(walkAnimationFlame_, walkAnimationData_.duration);
	gameObjectManager_->GetObj3dData(INameable::name_)->GetGameObject()->SkeletonUpdate(filePath, walkAnimationFlame_);

	shootTimerFlame_++;
	


	for (auto& state : states_) {
		auto& it = state.second;
		if (it)
		{
			it->Update(this);
		}
	}

	// �X�V��ɃL���[�����Ԃ��폜
	while (!statesToRemoveQueue_.empty()) {
		std::type_index typeIdx = statesToRemoveQueue_.front();
		states_.erase(typeIdx);
		statesToRemoveQueue_.pop();
	}
	//����
	if (velocity_.y <= -0.1f)
	{
		if (!IsInState<PlayerStateFall>())
		{
			AddState<PlayerStateFall>();
		}
	}

	///�_���[�W����
	if (IsInState<PlayerStateInvincible>())
	{
		damegeCoolTimer_ += DeltaTimer(damegeFlame_);

		if (damegeUpdateFunc_)
		{
			damegeUpdateFunc_();
		}

		//����l�ɂȂ�����
		if (damegeCoolTimer_ >= damageCoolTimerMax_)
		{
			damegeCoolTimer_ = 0;
			//�_���[�W���o�̏I��菈��
			if (damegeUpdateEndFunc_)
			{
				damegeUpdateEndFunc_();
			}
			this->MarkStateForRemoval<PlayerStateInvincible>();
		}
	}

	isShoot_ = false;

	TransformEular& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	transform.translate = Math::Vector::Add(transform.translate, velocity_);


	//�p�[�e�B�N���̔z�u�ʒu��Ŋ֐���
	auto& moveEmitParam = CharacterMoveParticle::GetInstance()->GetEmitter()->GetEmitParam()[particleMoveIndex_];
	moveEmitParam.translate = transform.translate;
	Math::Vector::Vector3 particleOffset = { 0.0f, aabb_.min.y / 2.0f + aabb_.min.y / 4.0f,-2.0f };
	moveEmitParam.translate.y += particleOffset.y;
	moveEmitParam.translate.z += particleOffset.z;

	//��������
	if (transform.translate.y <= -5.0f)
	{
		AddState<PlayerStateInvincible>();
		ResetPos();

		if (reduceHpFunc_)
		{
			reduceHpFunc_();
		}
	}

	//���񂾃A�j���[�V�������Đ����Ă�Ƃ�
	if (IsInState<PlayerStateDeadAnimation>())
	{
		auto& emit = deadParticle_->GetEmitter()->GetEmitParam()[0];
		auto& control = deadParticle_->GetEmitter()->GetControlParam()[0];

		control.useFlag_ = true;
		control.frequencyTime = 0.5f;
		emit.count = 3;

		emit.velocityMax = { 0.1f,0.1f,0.1f };
		emit.velocityMin = { -0.1f,-0.1f,-0.1f };
		emit.translate = transform.translate;
		return;
	}
}

void Player::OnCollision(ICollider* c, [[maybe_unused]] IObjectData* objData)
{
	if (kOnlyCollideWithBlocksid)
	{
		return;
	}

	if (c->GetId() == kGoalId)
	{
		if (!IsInState<PlayerStateGoalAnimation>())
		{
			AddState<PlayerStateGoalAnimation>();
		}
		return;
	}

	if (c->GetId() == kWarpGateId)
	{
		warpFilePath_ = gameObjectManager_->GetObj3dData(objData->GetName())->GetParamFilePaths()[0];
		AddState<PlayerStateWarpMove>();
	}

	if (!IsInState<PlayerStateInvincible>())
	{
		if (c->GetId() == kEnemyWalkId)
		{
			if (reduceHpFunc_)
			{
				reduceHpFunc_();
			}
			AddState<PlayerStateInvincible>();
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
			if (hitDirection == BOTTOM && velocity_.y <= -0.0f)
			{
				if (IsInState<PlayerStateJamp>())
				{
					this->MarkStateForRemoval<PlayerStateJamp>();
				}
				velocity_ = {};
			}
		}
		auto& transform = GameObjectManager::GetInstance()->GetObj3dData(INameable::name_)->GetWorldTransform().transform.translate;
		transform.x += extrusion_.x;
		transform.y += extrusion_.y;
	}
}

void Player::DrawParticle()
{
	deadParticle_->Draw();
}

void Player::Jamp()
{
	if (IsInState<PlayerStateRock>())
	{
		return;
	}

	if (!IsInState<PlayerStateJamp>())
	{
		AddState<PlayerStateJamp>();
	}
}

void Player::Move()
{
	//�Ή��̂Ƃ��͒ʂ��Ȃ�
	if (IsInState<PlayerStateRock>())
	{
		return;
	}
	//���񂾃��ʂ��Ȃ�
	if (IsInState<PlayerStateDeadAnimation>())
	{
		return;
	}

	if (!IsInState<PlayerStateWalk>())
	{
		AddState<PlayerStateWalk>();
	}

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
