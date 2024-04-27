#pragma once
#include"Vector/Vector3.h"
#include"Quaternion/Quaternion.h"
#include<json.hpp>

struct TransformEular
{
	Vector3 scale;
    Vector3 quaternion;
	Vector3 translate;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TransformEular, scale, quaternion, translate)

};