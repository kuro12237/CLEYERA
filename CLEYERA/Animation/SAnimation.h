#pragma once
#include"Pch.h"

namespace SAnimation
{
	struct KeyframeVector3
	{
		Vector3 value;
		float time;
	};

	struct KeyframeQuaternion
	{
		Quaternion value;
		float time;
	};

	template<typename tValue>
	struct KeyFrame
	{
		float time;
		tValue value;
	};

	struct NodeAnimation
	{
		std::vector<KeyframeVector3>translate;
		std::vector<KeyframeQuaternion>rotate;
		std::vector<KeyframeVector3>scale;
	};

	template<typename tValue>
	struct AnimationCurve
	{
		std::vector<KeyFrame<tValue>>keyframes;
	};

	struct Animation
	{
		uint32_t indexNumber = 0;
		float duration = 0;
		std::map<std::string, NodeAnimation>NodeAnimation;
	};
}
