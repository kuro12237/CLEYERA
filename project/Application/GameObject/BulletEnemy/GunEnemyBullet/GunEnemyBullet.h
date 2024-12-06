#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"

#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectId/GameObjectId.h"

class GunEnemyBullet:public IObjectData,public ICollider

{
public:
	GunEnemyBullet() {};
	~GunEnemyBullet() {};

	void Initialize();

	void Update();

	/// <summary>
	/// 当たった時
	/// </summary>
	void OnCollision(ICollider* c, IObjectData* objData)override;


#pragma region get

	bool GetIsDead() { return isDead_; }

#pragma endregion


private:

	bool isDead_ = false;

	float flame_ = 0.0f;
	int32_t deltaTime_ = 0;
	int32_t deltaTimeMax_ = 4;

};
