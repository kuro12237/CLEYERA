#pragma once
#include"SAnimation.h"
#include"Vector/VectorTransform.h"
#include"math/Quaternion/QuaternionTransform.h"

/// <summary>
/// アニメーション管理クラス
/// </summary>
class AnimationManager
{
public:

	static AnimationManager* GetInstance();

	/// <summary>
	/// 読み込み関数
	/// </summary>
	uint32_t LoadAnimation(const string& fileName);

	/// <summary>
	/// アニメーション再生
	/// </summary>
	/// <param name="keyflames"></param>
	/// <param name="time"></param>
	/// <returns></returns>
	static void ApplyAnimation(SAnimation::Skeleton& skeleton, SAnimation::Animation& animation, float time);

#pragma region Get
	SAnimation::Animation GetData(const string& fileName);
#pragma endregion

	static Math::Vector::Vector3 CalculateValue(const std::vector<SAnimation::KeyframeVector3>& keyflames, float time);
	static Math::Qua::Quaternion CalculateValue(const std::vector<SAnimation::KeyframeQuaternion>& keyflames, float time);

private:

	SAnimation::Animation LoadFile(const string& filename);

	uint32_t index_ = 0;
	std::map<std::string, SAnimation::Animation>datas_;

#pragma region 
	//Singleton
	AnimationManager() = default;
	~AnimationManager()  = default;
	AnimationManager(const AnimationManager&) = delete;
	const AnimationManager& operator=(const AnimationManager&) = delete;
#pragma endregion 
};