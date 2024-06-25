#pragma once
#include"Pch.h"

namespace Math
{
	namespace Vector
	{

		float Length(const Vector2& v);
		float Length(const Vector3& v);

		Vector3 Add(const Vector3& v1, const Vector3& v2);

		Vector3 Subtruct(const Vector3& v1, const Vector3& v2);

		Vector3 Multiply(const Vector3& v1, const float& v2);
		Vector3 Multiply(const Vector3& v1, const Vector3& v2);

		Vector3 TransformNormal(const Vector3& v, const Math::Matrix::Matrix4x4& m);
		Vector2 Normalize(const Vector2& v);
		Vector3 Normalize(const Vector3& v);

		Vector3 Lerp(const Vector3& a, const Vector3& b, const float t);

		float Dot(const Vector3& v1, const Vector3& v2);

		Vector3 SlerpFanc(Vector3 start, Vector3 end, float t);

		Vector4 Subtruct(const Vector4& v1, const Vector4& v2);

		Vector3 Cross(const Vector3 v1, const Vector3 v2);

		Vector3 TransformByMatrix(const Vector3 vector, const Math::Matrix::Matrix4x4 matrix);

		float easeOutBounce(float t);
	}
};

