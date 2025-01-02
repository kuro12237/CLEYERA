#pragma once

namespace Math
{
	namespace Vector
	{
		struct Vector4 final
		{
			float x;
			float y;
			float z;
			float w;
			NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vector4, x, y, z, w);
		};
	}
}