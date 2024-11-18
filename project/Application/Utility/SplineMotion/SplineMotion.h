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
	/// スプライン曲線補間関数Translate
	/// </summary>
	Math::Vector::Vector3 CatmullRomInterpolation();


	/// <summary>
	/// ターゲットの方向に向くための回転を計算
	/// </summary>
	Math::Vector::Vector3  CalculateSplineRotation();

	/// <summary>
	/// パラメーターの更新
	/// </summary>
	/// <param name="フレームMax値"></param>
	void UpdateParamerter(const float& kFlame);

#pragma region Get
	bool GetIsComplete() { return isComplete_; }
	bool GetIsStartFlag() { return isStartFlag_; }

	float GetFlame() { return flame_; }
	uint32_t GetTargetIndex() { return targetIndex_; }

	void SetP_Target(const Math::Vector::Vector3& target) { p_Target_ = &target; }
	void SetP_RailData(RailData& data) { p_RailData_ = &data; }
	void SetIsStartFlag(const bool& f) { isStartFlag_ = f; }
#pragma endregion

	void SetIsComplete(const bool& f) {
		isComplete_
			= f;
	}
private:

	RailData* p_RailData_ = nullptr;

	const Math::Vector::Vector3* p_Target_ = nullptr;

	uint32_t targetIndex_ = 0;

	float flame_ = 0.0f;

	bool isComplete_ = false;
	bool isStartFlag_ = false;

	Math::Vector::Vector3 position_ = {};
};

