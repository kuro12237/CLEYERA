#pragma once
#include"GameObject/ObjectInterface/ParticleComponent.h"

#include"GameObject/GameCollider/ColliderData.h"

#include"Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// キャラクターの動く時のパーティクル
/// </summary>
class PlayerMoveParticle :public ParticleComponent
{
public:

	PlayerMoveParticle() {};
	~PlayerMoveParticle() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

#pragma region Set

	void SetPlayerPos(const Math::Vector::Vector3& pos) { playerWorldPos_ = &pos; }

	void SetIsEmit(bool f) { isEmit_ = f; };
#pragma endregion

private:

	const Math::Vector::Vector3* playerWorldPos_ = nullptr;

	bool isEmit_ = false;
};

