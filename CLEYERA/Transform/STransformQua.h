#pragma once
#include"Vector3.h"
#include"Quaternion/Quaternion.h"
#include<json.hpp>

struct TransformQua
{
	Vector3 scale;
	Quaternion quaternion;
	Vector3 translate;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformQua, scale, quaternion, translate)

};