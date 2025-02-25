#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Utility/convert/convert.h"

#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"state/GunEnemyStateMove.h"
#include"state/GunEnemyStateDeadAnimation.h"

#include"GunEnemyBullet/GunEnemyBullet.h"
#include"IGunEnemy.h"

class GunEnemy : public IGunEnemy
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
	void OnCollision(ObjectComponent* objData)override;

	void CreateBullet(const Math::Vector::Vector3& Pos);

#pragma region Get
	int32_t GetEnemyNumber() { return enemyNumber_; }
	vector<shared_ptr<GunEnemyBullet>>GetBullets() { return bullets_; }
#pragma endregion


private:

	uint32_t modelHandle_ = 0;

	vector<shared_ptr<GunEnemyBullet>>bullets_;
	queue<uint32_t>deadBulletIndex_;

};