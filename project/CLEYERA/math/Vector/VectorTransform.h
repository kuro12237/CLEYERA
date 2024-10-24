#pragma once
#include"Pch.h"

namespace Math
{
	namespace Vector
	{

		float degreesToRadians(float degrees);
		
		float Length(const Vector2& v);
		float Length(const Vector3& v);

		Vector3 Add(const Vector3& v1, const Vector3& v2);

		Vector3 Subtruct(const Vector3& v1, const Vector3& v2);

		Vector3 Multiply(const Vector3& v1, const float& v2);
		Vector3 Multiply(const Vector3& v1, const Vector3& v2);
		Vector2 Multiply(const Vector2& v1, const float v);

		Vector3 TransformNormal(const Vector3& v, const Math::Matrix::Matrix4x4& m);
		float Normalize(const float& v);
		Vector2 Normalize(const Vector2& v);
		Vector3 Normalize(const Vector3& v);

		float Lerp(const float& a, const float& b, const float t);
		Vector3 Lerp(const Vector3& a, const Vector3& b, const float t);

		float Dot(const Vector3& v1, const Vector3& v2);

		Vector3 SlerpFanc(Vector3 start, Vector3 end, float t);

		Vector4 Subtruct(const Vector4& v1, const Vector4& v2);

		Vector3 Cross(const Vector3 v1, const Vector3 v2);

		Vector3 TransformByMatrix(const Vector3 vector, const Math::Matrix::Matrix4x4 matrix);

		float easeOutBounce(float t);
		float easeOutSine(float t);
		float easeInSine(float t);

		float CalcXRotation(const Vector3& rotate);
		float CalcYRotation(const Vector3& rotate);

		Vector3 LerpEaseOutSine(const Vector3& a, const Vector3& b, const float t);
		Vector3 LerpEaseInSine(const Vector3& a, const Vector3& b, const float t);

		float LerpEaseOutSine(const float& a, const float& b, const float t);
	    float LerpEaseInSine(const float& a, const float& b, const float t);

		template<typename T>
		T easeOutExpo(const T& a, const T& b, const float t)
		{
			T result;
			float easeT = t == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * t);
			result = a + easeT * (b - a);
			return result;
		}
		template<typename T>
		T EaseOutQuad(const T& start, const T& end, float t) {
			// EaseOutQuad‚Ì•âŠÔŒvŽZ
			t = 1 - (1 - t) * (1 - t);

			// start‚Æend‚ÌŠÔ‚Åt‚É‰ž‚¶‚Ä•âŠÔ
			return start + t * (end - start);
		}

		Vector3 Catmull_Rom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t);

	}
};

