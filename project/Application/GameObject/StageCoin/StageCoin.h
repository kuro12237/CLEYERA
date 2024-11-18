#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/convert/convert.h"

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

#pragma region Get

	 
#pragma endregion

#pragma region Set
	void SetCoinNumber(const int32_t& number) { coinNumber_ = number; }
#pragma endregion


private:

	int32_t coinNumber_ = 0;

	float animationFlame_ = 0.0f;
	SAnimation::Animation animationData_{};


};