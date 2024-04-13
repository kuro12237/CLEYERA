#pragma once
#include"Pch.h"

struct TransformQua
{
	Vector3 scale;
	Quaternion quaternion;
	Vector3 translate;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformQua, scale, quaternion, translate)

};