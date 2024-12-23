#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/convert/convert.h"
#include"GameObject/GameCollider/ICollider.h"

#include"Utility/ObjectId/GameObjectId.h"
#include"Utility/ColorConverter/ColorConverter.h"
/// <summary>
/// コインオブジェクト
/// /// </summary>
class StageCoin:public IObjectData
{
public:
	StageCoin() {};
	~StageCoin() {};

	void Initilaize();

	void Update();

	void OnCollision(IObjectData* objData)override;

#pragma region Get
	bool GetIsDead() { return isDead_; }
#pragma endregion

#pragma region Set
	void SetCoinNumber(const int32_t& number) { coinNumber_ = number; }
#pragma endregion


private:

	int32_t coinNumber_ = 0;
	bool isDead_ = false;

	float animationFlame_ = 0.0f;
	SAnimation::Animation animationData_{};


};