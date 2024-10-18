#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"

/// <summary>
/// スプライン曲線をするためのクラス
/// </summary>
class SplineMotion
{
public:
	SplineMotion() {};
	~SplineMotion() {};

	/// <summary>
	/// スプライン曲線補間関数
	/// </summary>
	Math::Vector::Vector3 CatmullRomInterpolation();

	/// <summary>
	/// パラメーターの更新
	/// </summary>
	/// <param name="フレームMax値"></param>
	void UpdateParamerter(const float &kFlame);

#pragma region Get


#pragma endregion



private:

	const RailData* p_RailData_ = nullptr;

	uint32_t selectIndex_ = 0;

	float flame_ = 0.0f;

	bool isComplete_ = false;

};

