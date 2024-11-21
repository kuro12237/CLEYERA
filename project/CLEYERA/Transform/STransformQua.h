#pragma once
#include"Pch.h"



namespace Engine::Transform
{


	/// <summary>
	/// transform,élå≥êîä‹Çﬁ
	/// </summary>
	struct TransformQua
	{
		Math::Vector::Vector3 scale;
		Math::Qua::Quaternion quaternion;
		Math::Vector::Vector3 translate;
		Math::Vector::Vector3 rotate;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformQua, scale, quaternion, translate, rotate)

	};
}
