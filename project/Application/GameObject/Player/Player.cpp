#include "Player.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void Player::Initialize()
{
	INameable::name_ = "Player";
	jsonGropName_ = INameable::name_;
	CreateJsonData();

	//状態異常のステート
	//id設定
	id_ = kPlayerId;
	//当たり判定設定
	this->isExtrusion_ = true;
	SetObjectData(gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform);
	aabb_ = gameObjectManager_->GetObj3dData(INameable::name_)->GetAABB();
	attribute_ = CollisionMask::kPlayerAttribute;
	mask_ = CollisionMask::kPlayerMask;

	//TransformGet
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;

	//Scale値を外部から読み込む
	float dfScale = 0.0f;
	AddJsonItem<float>("DefaultScale", dfScale);
	dfScale = GetJsonItem<float>("DefaultScale");
	transform.scale = { dfScale,dfScale,dfScale };

	//スタート入りの記録
	resetPos_ = transform.translate;

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

	AnimationManager::GetInstance()->LoadAnimation("FallDown");

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

	shootTimerFlame_++;

	//状態更新
	for (auto& state : states_) {
		auto& it = state.second;
		if (it)
		{
			it->Update(this);
		}
	}
	gameObjectManager_->GetObj3dData(INameable::name_)->GetGameObject()->SkeletonUpdate();


	// 更新後にキューから状態を削除
	while (!statesToRemoveQueue_.empty()) {
		std::type_index typeIdx = statesToRemoveQueue_.front();
		states_.erase(typeIdx);
		statesToRemoveQueue_.pop();
	}

	//落下
	if (velocity_.y <= -0.1f)
	{
		if (!IsInState<PlayerStateFall>())
		{
			AddState<PlayerStateFall>();
		}
	}

	///ダメージ処理
	if (IsInState<PlayerStateInvincible>())
	{
		damegeCoolTimer_ += DeltaTimer(damegeFlame_);

		if (damegeUpdateFunc_)
		{
			damegeUpdateFunc_();
		}

		//上限値になったら
		if (damegeCoolTimer_ >= damageCoolTimerMax_)
		{
			damegeCoolTimer_ = 0;
			//ダメージ演出の終わり処理
			if (damegeUpdateEndFunc_)
			{
				damegeUpdateEndFunc_();
			}
			this->MarkStateForRemoval<PlayerStateInvincible>();
		}
	}

	isShoot_ = false;

	TransformUpdate();

	TransformEular& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;

	//パーティクルの配置位置後で関数化
	auto& moveEmitParam = CharacterMoveParticle::GetInstance()->GetEmitter()->GetEmitParam()[particleMoveIndex_];
	moveEmitParam.translate = transform.translate;
	Math::Vector::Vector3 particleOffset = { 0.0f, aabb_.min.y / 2.0f + aabb_.min.y / 4.0f,-2.0f };
	moveEmitParam.translate.y += particleOffset.y;
	moveEmitParam.translate.z += particleOffset.z;
	moveEmitParam.scaleSizeMin = { 0.1f,0.1f,0.1f };
	moveEmitParam.scaleSizeMax = { 0.1f,0.1f,0.1f };
	moveEmitParam.scaleVelocityMax = { 0.05f,0.05f,0.05f };
	moveEmitParam.scaleVelocityMin = { 0.05f,0.05f,0.05f };


	//落ちたら
	if (transform.translate.y <= -5.0f)
	{
		//無敵化
		AddState<PlayerStateInvincible>();
		ResetPos();

		if (reduceHpFunc_)
		{
			reduceHpFunc_();
		}
	}

	//死んだアニメーションを再生してるとき
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

	if (!IsInState<PlayerStateJamp>() && velocity_.y == 0.0f)
	{
		AddState<PlayerStateJamp>();
	}
}

void Player::Move()
{
	//石化のときは通さない
	if (IsInState<PlayerStateRock>())
	{
		return;
	}
	//死んだラ通さない
	if (IsInState<PlayerStateDeadAnimation>())
	{
		return;
	}
	if (IsInState<PlayerStateDash>())
	{
		return;
	}


	if (!IsInState<PlayerStateWalk>())
	{
		AddState<PlayerStateWalk>();
	}

}

void Player::Shoot()
{
	if (shootTimerFlame_ >= shootTimerMax_)
	{
		isShoot_ = true;
		shootTimerFlame_ = 0;
	}
}

void Player::Dash()
{
	if (IsInState<PlayerStateJamp>())
	{
		return;
	}
	if (IsInState<PlayerStateFall>())
	{
		return;
	}

	//石化のときは通さない
	if (IsInState<PlayerStateRock>())
	{
		return;
	}
	//死んだラ通さない
	if (IsInState<PlayerStateDeadAnimation>())
	{
		return;
	}

	if (IsInState<PlayerStateWalk>())
	{
		MarkStateForRemoval<PlayerStateWalk>();
	}

	if (!IsInState<PlayerStateDash>())
	{
		AddState<PlayerStateDash>();
	}
}

void Player::TransformUpdate()
{
	TransformEular& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	transform.translate = Math::Vector::Add(transform.translate, velocity_);

	const float degrees = 90.0f;
	float radian = {};
	if (velocity_.x > 0.0f)
	{
		radian = Math::Vector::degreesToRadians(degrees);
	}
	//左
	if (velocity_.x < 0.0f)
	{
		radian = Math::Vector::degreesToRadians(-degrees);
	}
	transform.rotate.y = radian;

}
