#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectInterface/IObjectData.h"

#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"state/GunEnemyStateMove.h"
#include"state/GunEnemyStateDeadAnimation.h"

#include"GunEnemyBullet/GunEnemyBullet.h"

class GunEnemy :public IObjectData, public ICollider
{
public:
	GunEnemy() {};
	~GunEnemy() {};

	/// <summary>
    /// 初期化
    /// </summary>
	void Initialize();

	void Update();

	/// <summary>
	/// 当たった時
	/// </summary>
	void OnCollision(ICollider* c, IObjectData* objData)override;

	void ChangeState(unique_ptr<IGunEnemyState>state);

	void CreateBullet(const Math::Vector::Vector3 &Pos);

#pragma region Get

	bool &GetIsEnd() { return isEnd_; }
	float GetSpeed() { return speed_; }
	bool &GetIsDead() { return isDead_; }
	int32_t GetEnemyNumber() { return enemyNumber_; }
	vector<shared_ptr<GunEnemyBullet>>GetBullets() { return bullets_; }
#pragma endregion

#pragma region Set
	void SetEnemyNumber(int32_t number) { enemyNumber_ = number; }
#pragma endregion

private:
	bool IsHit_ = false;
	bool isDead_ = false;
	bool isEnd_ = false;

	float speed_ = -0.1f;

	int32_t enemyNumber_ = 0;

	uint32_t modelHandle_ = 0;

	unique_ptr<IGunEnemyState>state_ = nullptr;

	vector<shared_ptr<GunEnemyBullet>>bullets_;
	queue<uint32_t>deadBulletIndex_;

};