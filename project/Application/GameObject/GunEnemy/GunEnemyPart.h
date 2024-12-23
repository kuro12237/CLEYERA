#pragma once


#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/convert/convert.h"

#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"state/GunEnemyStateMove.h"
#include"state/GunEnemyStateDeadAnimation.h"

#include"GunEnemyBullet/GunEnemyBullet.h"


/// <summary>
/// 右足
/// </summary>
class GunEnemyPart :public IGunEnemy
{
public:
	GunEnemyPart() {};
	~GunEnemyPart() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Update();

	/// <summary>
	/// 当たった時
	/// </summary>
	void OnCollision(IObjectData* objData)override;

#pragma region Set
	void SetIsCoreEnd(bool& f) { isCoreEnd_ = &f; }
#pragma endregion

private:

	bool* isCoreEnd_ = nullptr;
};
