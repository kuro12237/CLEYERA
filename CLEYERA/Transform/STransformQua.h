#pragma once
#include"Pch.h"

struct TransformQua
{
	Math::Vector::Vector3 scale;
	Math::Qua::Quaternion quaternion;
	Math::Vector::Vector3 translate;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformQua, scale, quaternion, translate)

};