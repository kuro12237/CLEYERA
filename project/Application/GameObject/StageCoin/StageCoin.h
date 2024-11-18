#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/convert/convert.h"
#include"GameObject/GameCollider/ICollider.h"

/// <summary>
/// �R�C���I�u�W�F�N�g
/// /// </summary>
class StageCoin:public IObjectData,public ICollider
{
public:
	StageCoin() {};
	~StageCoin() {};

	void Initilaize();

	void Update();

	void OnCollision(ICollider* c, IObjectData* objData)override;

#pragma region Get
	bool GetIsDead() const { return &isDead_; }
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