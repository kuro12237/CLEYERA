#pragma once
#include"GameObject/ObjectInterface/ObjectComponent.h"

#include"Utility/ObjectId/GameObjectId.h"

class GunEnemyBullet:public ObjectComponent

{
public:
	GunEnemyBullet() {};
	~GunEnemyBullet() {};

	void Initialize();

	void Update();

	/// <summary>
	/// 当たった時
	/// </summary>
	void OnCollision(ObjectComponent* objData)override;


#pragma region get

	bool GetIsDead() { return isDead_; }

#pragma endregion


private:

	bool isDead_ = false;

	float flame_ = 0.0f;
	int32_t deltaTime_ = 0;
	int32_t deltaTimeMax_ = 4;

};
