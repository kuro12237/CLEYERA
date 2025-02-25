#pragma once

#include"GameObject/ObjectInterface/ObjectComponent.h"

#include"state/IPlayerBulletState.h"
#include"state/PlayerBulletStateNone.h"

#include"Utility/ObjectId/GameObjectId.h"

/// <summary>
/// 銃の弾
/// </summary>
class PlayerBullet:public ObjectComponent
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="number"></param>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	///　当たった時の
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ObjectComponent* objData)override;

#pragma region Set
	void SetSpownPos(Math::Vector::Vector3 pos) { spownPos_ = pos; }
	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }
	void SetPlayerSpeed(Math::Vector::Vector3 v) { playerSpeed_ = v; }
	void SetBuletName(string num) { name_ = num; }
#pragma endregion

#pragma region Get
	bool GetIsDeadFlag() { return isDead_; }
#pragma endregion

private:

	unique_ptr<IPlayerBulletState>state_ = nullptr;

	Math::Vector::Vector3 playerSpeed_ = {};
	Math::Vector::Vector3 spownPos_ = {};
	bool isDead_ = false;
	uint32_t timer_ = 0;
	uint32_t timerMax_ = 60;
	const float speed_ = 0.75f;

};