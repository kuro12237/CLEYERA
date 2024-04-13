#pragma once

struct Quaternion
{
	float x, y, z, w;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Quaternion, x, y, z, w)

};