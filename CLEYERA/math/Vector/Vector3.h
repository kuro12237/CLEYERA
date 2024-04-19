#pragma once
#include<json.hpp>

namespace Math
{
	namespace Vector
	{
		struct Vector3 final
		{
			float x;
			float y;
			float z;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vector3, x, y, z)

		};
	}
}