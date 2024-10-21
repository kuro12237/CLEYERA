#include "VectorTransform.h"

using namespace Math::Vector;

float Math::Vector::degreesToRadians(float degrees)
{
	return degrees * (float(std::numbers::pi) / 180.0f);
}

float Math::Vector::Length(const Vector2& v)
{
	float result{};
	result = sqrtf(v.x * v.x + v.y * v.y);
	return result;
}

float Math::Vector::Length(const Vector3& v)
{
	float result{};
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 Math::Vector::Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Math::Vector::Subtruct(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Math::Vector::Multiply(const Vector3& v1, const float& v2)
{
	Vector3 result{};
	result.x = v1.x * v2;
	result.y = v1.y * v2;
	result.z = v1.z * v2;
	return result;
}

Vector3 Math::Vector::Multiply(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

Vector2 Math::Vector::Multiply(const Vector2& v1, const float v)
{
	Vector2 result{};
	result.x = v1.x * v;
	result.y = v1.y * v;
	return result;
}

Vector3 Math::Vector::TransformNormal(const Vector3& v, const Math::Matrix::Matrix4x4& m)
{
	Vector3 result
	{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};

	return result;

}

float Math::Vector::Normalize(const float& v)
{
	float result{};
	float length = sqrtf(v * v);
	if (length != 0.0f) {
		result = v / length;
	}
	return result;
}

Vector2 Math::Vector::Normalize(const Vector2& v)
{
	Vector2 result{};
	float length = Length(v);
	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
	}
	return result;
}

Vector3 Math::Vector::Normalize(const Vector3& v)
{
	Vector3 result{};
	float length = Length(v);
	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}

float Math::Vector::Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

float Math::Vector::Lerp(const float& a, const float& b, const float t)
{
	float  P;
	P = a + t * (b - a);
	return P;
}

Vector3 Math::Vector::Lerp(const Vector3& a, const Vector3& b, const float t) {

	Vector3 P;
	P.x = a.x + t * (b.x - a.x);
	P.y = a.y + t * (b.y - a.y);
	P.z = a.z + t * (b.z - a.z);
	return P;
}

Vector3 Math::Vector::SlerpFanc(Vector3 start, Vector3 end, float t)
{
	float dot = start.x * end.x + start.y * end.y + start.z * end.z;
	float theta = std::acos(dot) * t;
	Vector3 relative = { end.x - start.x * dot, end.y - start.y * dot, end.z - start.z * dot };
	relative = Normalize(relative);
	Vector3 result = {
		start.x * std::cosf(theta) + relative.x * std::sinf(theta),
		start.y * std::cosf(theta) + relative.y * std::sinf(theta),
		start.z * std::cosf(theta) + relative.z * std::sinf(theta)
	};

	return result;
}

Vector4 Math::Vector::Subtruct(const Vector4& v1, const Vector4& v2)
{
	Vector4 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return result;
}

Vector3 Math::Vector::Cross(const Vector3 v1, const Vector3 v2)
{
	Vector3 result = { 0.0f,0.0f,0.0f };
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}


Vector3 Math::Vector::TransformByMatrix(const Vector3 vector, const Math::Matrix::Matrix4x4 matrix)
{
	Vector3 result{};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z *
		matrix.m[2][0] + 1.0f * matrix.m[3][0];

	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z *
		matrix.m[2][1] + 1.0f * matrix.m[3][1];

	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z *
		matrix.m[2][2] + 1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z *
		matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return  result;
}

float Math::Vector::easeOutBounce(float t)
{

	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (t < 1.0f / d1) {
		return n1 * t * t;
	}
	else if (t < 2.0f / d1)
	{
		return n1 * (t - 1.5f / d1) * t + 0.75f;
	}
	else if (t < 2.5f / d1)
	{
		return n1 * (t - 2.25f / d1) * t + 0.9375f;
	}
	else
	{
		return n1 * (t - 2.625f / d1) * t + 0.984375f;
	}
}

float Math::Vector::easeOutSine(float t)
{
  return  sinf((t * static_cast<float>(numbers::pi)) / 2);
}

float Math::Vector::easeInSine(float t)
{
	return 1 - cosf((t * static_cast<float>(numbers::pi)) / 2);
}

float Math::Vector::CalcXRotation(const Vector3& rotate)
{
	float velocityXZ = sqrt(rotate.x * rotate.x + rotate.z * rotate.z);  // XZ平面の長さ
	float heightY = -rotate.y;
	float sinTheta = heightY / sqrt(heightY * heightY + velocityXZ * velocityXZ);
	return asin(sinTheta);  // asinを使って角度を計算
}

float Math::Vector::CalcYRotation(const Vector3& rotate)
{
	Vector3 forward = { 0.0f, 0.0f, 1.0f };  // 基準ベクトル (Z方向)
	float dotProduct = forward.x * rotate.x + forward.z * rotate.z;
	float magnitudeForward = sqrt(forward.x * forward.x + forward.z * forward.z);
	float magnitudeRotate = sqrt(rotate.x * rotate.x + rotate.z * rotate.z);

	// コサインの逆数を使って角度を計算
	float cosTheta = dotProduct / (magnitudeForward * magnitudeRotate);
	float yRotation = acos(cosTheta);

	// クロス積を使って回転方向（符号）を決定
	float crossProduct = forward.x * rotate.z - forward.z * rotate.x;
	if (crossProduct < 0) {
		yRotation = -yRotation;
	}

	return yRotation;
}

Vector3 Math::Vector::LerpEaseOutSine(const Vector3& a, const Vector3& b, const float t)
{
	float easedT = easeOutSine(t);

	// 補間
	return Lerp(a, b, easedT);
}

Vector3 Math::Vector::LerpEaseInSine(const Vector3& a, const Vector3& b, const float t)
{
	float easedT = easeInSine(t);

	// 補間
	return Lerp(a, b, easedT);
}

float Math::Vector::LerpEaseOutSine(const float& a, const float& b, const float t)
{
	float easedT = easeOutSine(t);

	// 補間
	return Lerp(a, b, easedT);
}

float Math::Vector::LerpEaseInSine(const float& a, const float& b, const float t)
{
	float easedT = easeInSine(t);

	// 補間
	return Lerp(a, b, easedT);
}

Vector3 Math::Vector::Catmull_Rom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t)
{

	float t2 = t * t;
	float t3 = t * t * t;
	return Vector3(
		//x
		0.5f * ((-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3 +
			(2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 + (-p0.x + p2.x) * t + 2 * p1.x),
		//y
		0.5f * ((-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3 +
			(2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 + (-p0.y + p2.y) * t + 2 * p1.y),
		//z
		0.5f * ((-p0.z + 3 * p1.z - 3 * p2.z + p3.z) * t3 +
			(2 * p0.z - 5 * p1.z + 4 * p2.z - p3.z) * t2 + (-p0.z + p2.z) * t + 2 * p1.z)
	);
}


