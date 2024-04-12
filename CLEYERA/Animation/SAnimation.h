#pragma once
#include"Pch.h"

namespace SAnimation
{

	template<typename tValue>
	struct KeyFrame
	{
		float time;
		tValue value;
	};

	using KeyframeQuaternion = KeyFrame<Quaternion>;
	using KeyframeVector3 = KeyFrame<Vector3>;

	template<typename tValue>
	struct AnimationCurve
	{
		std::vector<KeyFrame<tValue>>keyframes;
	};

	struct NodeAnimation
	{
		AnimationCurve<Vector3>translate;
		AnimationCurve<Quaternion>rotate;
		AnimationCurve<Vector3>scale;
	};

	struct Animation
	{
		uint32_t indexNumber = 0;
		float duration = 0;
		std::map<std::string, NodeAnimation>NodeAnimation;
	};
}
