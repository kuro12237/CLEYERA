#pragma once
#include"Pch.h"
#include"Transform/STransformQua.h"


/// <summary>
/// アニメーション構造体
/// </summary>
namespace SAnimation
{

	template<typename tValue>
	struct KeyFrame
	{
		float time;
		tValue value;
	};

	using KeyframeQuaternion = KeyFrame< Math::Qua::Quaternion>;
	using KeyframeVector3 = KeyFrame<Math::Vector::Vector3>;

	template<typename tValue>
	struct AnimationCurve
	{
		std::vector<KeyFrame<tValue>>keyframes;
	};

	/// <summary>
	/// NodeAnimation構造体
	/// </summary>
	struct NodeAnimation
	{
		AnimationCurve<Math::Vector::Vector3>translate;
		AnimationCurve<Math::Qua::Quaternion>rotate;
		AnimationCurve<Math::Vector::Vector3>scale;
	};

	/// <summary>
	/// 体のデータ
	/// </summary>
	struct Animation
	{
		uint32_t indexNumber = 0;
		float duration = 0;
		std::map<std::string, NodeAnimation>NodeAnimation;
	};

	/// <summary>
	/// ジョイント構造体
	/// </summary>
	struct Joint {
		Engine::Transform::TransformQua transform;
		Math::Matrix::Matrix4x4 localMatrix;
		Math::Matrix::Matrix4x4 skeletonSpaceMatrix;
		std::string name;
		std::vector<int32_t>childlen;
		int32_t index;
		std::optional<int32_t>parent;
	};
	
	/// <summary>
	/// スケルトン構造体
	/// </summary>
	struct Skeleton
	{
		int32_t root;
		std::map<std::string, int32_t>jointMap;
		std::vector<Joint>joints;

	};
}
