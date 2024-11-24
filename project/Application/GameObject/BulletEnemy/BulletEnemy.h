#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectInterface/IObjectData.h"

#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

class BulletEnemy :public IObjectData, public ICollider
{
public:
	BulletEnemy() {};
	~BulletEnemy() {};

	/// <summary>
    /// 初期化
    /// </summary>
	void Initialize();

	void Update();

	/// <summary>
	/// 当たった時
	/// </summary>
	void OnCollision(ICollider* c, IObjectData* objData)override;


#pragma region Get

	bool GetIsEnd() { return isEnd_; }

#pragma endregion

private:
	bool IsHit_ = false;
	bool isDead_ = false;
	bool isEnd_ = false;

	float speed_ = -0.1f;

};