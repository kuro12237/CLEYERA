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

	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetId(ObjectId::kPlayerId);
	collider_->SetIsExtrusion(true);
	collider_->SetMask(CollisionMask::kPlayerMask);
	collider_->SetAttribute(CollisionMask::kPlayerAttribute);
	
	//TransformGet
	auto& transform = objectData_.lock()->GetWorldTransform().transform;

	//Scale値を外部から読み込む
	float dfScale = 0.0f;
	AddJsonItem<float>("DefaultScale", dfScale);
	dfScale = GetJsonItem<float>("DefaultScale");
	transform.scale = { dfScale,dfScale,dfScale };

	//スタート入りの記録
	resetPos_ = transform.translate;
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

		ImGui::Text("%d", static_cast<int>(states_.size()));

		ImGui::TreePop();
	}
}

void Player::Update()
{
	auto& objData = gameObjectManager_->GetObj3dData(INameable::name_);

	shootTimerFlame_++;

	//状態更新
	for (auto& state : states_) {
		auto& it = state.second;
		if (it)
		{
			it->Update(this);
		}
	}
	objData->GetGameObject()->SkeletonUpdate();


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

	if (!isAim_ && IsInState<PlayerStateAim>())
	{
		this->MarkStateForRemoval<PlayerStateAim>();
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

	isAim_ = false;
	isShoot_ = false;

	TransformUpdate();

	TransformEular& transform = objData->GetWorldTransform().transform;

	if (IsInState<PlayerStateAim>())
	{
		float rotateY = gameObjectManager_->GetObj3dData("PlayerGun")->GetWorldTransform().transform.rotate.y;
		const float degrees = 90.0f;
		float radian = 0.0f;

		if (rotateY >= Math::Vector::degreesToRadians(90.0f))
		{
			radian = Math::Vector::degreesToRadians(-degrees);
		}
		else
		{
			radian = Math::Vector::degreesToRadians(degrees);
		}

		transform.rotate.y = radian;
	}
	else {
		RotateUpdate();
	}

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
}

void Player::OnCollision([[maybe_unused]] ObjectComponent* objData)
{
	auto c = objData->GetCollider();

	if (ObjectId::kOnlyCollideWithBlocksid)
	{
		return;
	}

	if (c->GetId() == ObjectId::kGoalId)
	{
		hitGoalName_ = objData->GetName();
		if (!IsInState<PlayerStateGoalAnimation>())
		{
			AddState<PlayerStateGoalAnimation>();
		}
		return;
	}

	if (c->GetId() == ObjectId::kWarpGateId)
	{
		warpFilePath_ = gameObjectManager_->GetObj3dData(objData->GetName())->GetParamFilePaths()[0];
		AddState<PlayerStateWarpMove>();
	}

	if (!IsInState<PlayerStateInvincible>())
	{
		if (c->GetId() == ObjectId::kEnemyWalkId)
		{
			if (reduceHpFunc_)
			{
				reduceHpFunc_();
			}
			AddState<PlayerStateInvincible>();
		}

		if (c->GetId() == ObjectId::kGunEnemyId)
		{
			if (reduceHpFunc_)
			{
				reduceHpFunc_();
			}
			AddState<PlayerStateInvincible>();
		}
		if (c->GetId() == ObjectId::kGunEnemyBulletId)
		{
			if (reduceHpFunc_)
			{
				reduceHpFunc_();
			}
			AddState<PlayerStateInvincible>();
		}
	}

	if (c->GetId() == ObjectId::kNormalBlock)
	{
		for (auto& hitDirection : collider_->GetHItDirection())
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
	
		auto& transform = objectData_.lock()->GetWorldTransform().transform;

		transform.translate.x += collider_->GetExtrusion().x;
		transform.translate.y += collider_->GetExtrusion().y;
	}
}

void Player::RotateUpdate()
{
	TransformEular& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;

	const float degrees = 90.0f;
	float radian = 0.0f;
	if (velocity_.x > 0.0f)
	{
		radian = Math::Vector::degreesToRadians(degrees);
		transform.rotate.y = radian;
	}
	//左
	if (velocity_.x < 0.0f)
	{
		radian = Math::Vector::degreesToRadians(-degrees);
		transform.rotate.y = radian;
	}
}

void Player::Jamp()
{

	CheckStatePush<PlayerStateAim>();
	CheckStatePush<PlayerStateRock>();
	CheckStatePush<PlayerStateDeadAnimation>();

	if (IsCheckStateRetuen())
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

	CheckStatePush<PlayerStateAim>();
	CheckStatePush<PlayerStateRock>();
	CheckStatePush<PlayerStateDeadAnimation>();
	CheckStatePush<PlayerStateDash>();

	if (IsCheckStateRetuen())
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
	//指定のステートの場合通さない
	CheckStatePush<PlayerStateAim>();
	CheckStatePush<PlayerStateRock>();
	CheckStatePush<PlayerStateDeadAnimation>();
	CheckStatePush<PlayerStateFall>();
	CheckStatePush<PlayerStateJamp>();
	if (IsCheckStateRetuen())
	{
		return;
	}

	//歩きののとき削除
	if (IsInState<PlayerStateWalk>())
	{
		MarkStateForRemoval<PlayerStateWalk>();
	}

	//ダッシュがなかったら追加
	if (!IsInState<PlayerStateDash>())
	{
		AddState<PlayerStateDash>();
	}
}

void Player::Aim()
{
	isAim_ = true;
	//指定のステートの場合通さない
	CheckStatePush<PlayerStateRock>();
	CheckStatePush<PlayerStateDeadAnimation>();
	CheckStatePush<PlayerStateFall>();
	CheckStatePush<PlayerStateJamp>();

	if (IsCheckStateRetuen())
	{
		return;
	}

	if (!IsInState<PlayerStateAim>())
	{
		AddState<PlayerStateAim>();
	}
}

void Player::TransformUpdate()
{
   TransformEular &transform = objectData_.lock()->GetWorldTransform().transform;

	transform.translate = Math::Vector::Add(transform.translate, velocity_);
}
