#pragma once
#include"Pch.h"

namespace Math
{
	namespace Vector
	{

		float degreesToRadians(float degrees);
		float Length(const Vector2& v);
		float Length(const Vector3& v);

		template <typename T>
		T easeOutExpo(T x);

		Vector3 Add(const Vector3& v1, const Vector3& v2);

		Vector3 Subtruct(const Vector3& v1, const Vector3& v2);

		Vector3 Multiply(const Vector3& v1, const float& v2);
		Vector3 Multiply(const Vector3& v1, const Vector3& v2);

		Vector3 TransformNormal(const Vector3& v, const Math::Matrix::Matrix4x4& m);
		float Normalize(const float& v);
		Vector2 Normalize(const Vector2& v);
		Vector3 Normalize(const Vector3& v);

		Vector3 Lerp(const Vector3& a, const Vector3& b, const float t);

		float Dot(const Vector3& v1, const Vector3& v2);

		Vector3 SlerpFanc(Vector3 start, Vector3 end, float t);

		Vector4 Subtruct(const Vector4& v1, const Vector4& v2);

		Vector3 Cross(const Vector3 v1, const Vector3 v2);

		Vector3 TransformByMatrix(const Vector3 vector, const Math::Matrix::Matrix4x4 matrix);

		float easeOutBounce(float t);

		template<typename T>
		T easeOutExpo(const T& a, const T& b, const float t)
		{
			T result;
			float easeT = t == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * t);
			result = a + easeT * (b - a);
			return result;
		}
	}
};

