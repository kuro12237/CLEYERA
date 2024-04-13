#include "VectorTransform.h"

float Math::Vector::Length(const Vector3& v)
{
	float result{};
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 Math::Vector::Add(const Vector3 &v1, const Vector3 &v2)
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

Vector3 Math::Vector::TransformNormal(const Vector3& v, const Matrix4x4& m)
{
	Vector3 result
	{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};

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

Vector3 Math::Vector::Lerp(const Vector3& a, const Vector3& b, const float t) {
	return Vector3{ a.x + t * (b.x - a.x),a.y + t * (b.y - a.y),a.z + t * (b.z - a.z)};
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


Vector3 Math::Vector::TransformByMatrix(const Vector3 vector, const Matrix4x4 matrix)
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


