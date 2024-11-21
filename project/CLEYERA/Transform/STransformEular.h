#pragma once
#include"Vector/Vector3.h"
#include"Quaternion/Quaternion.h"
#include<json.hpp>



namespace Engine::Transform
{

	/// <summary>
	/// transform
	/// </summary>
	struct TransformEular
	{
		Math::Vector::Vector3 scale;
		Math::Vector::Vector3 rotate;
		Math::Vector::Vector3 translate;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformEular, scale, rotate, translate)

	};
}