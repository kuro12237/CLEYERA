#pragma once
#include"SAnimation.h"
#include"VectorTransform.h"
#include"math/Quaternion/QuaternionTransform.h"

class AnimationManager
{
public:

	static AnimationManager* GetInstance();

	uint32_t LoadAnimation(const string& fileName);

	SAnimation::Animation GetData(const string& fileName);

	static Vector3 CalculateValue(const std::vector<SAnimation::KeyframeVector3>& keyflames, float time);
	static Quaternion CalculateValue(const std::vector<SAnimation::KeyframeQuaternion>& keyflames, float time);

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