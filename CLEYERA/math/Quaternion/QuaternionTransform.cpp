#include "QuaternionTransform.h"

Matrix4x4 QuaternionTransform::MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Matrix4x4 result{};
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);

	result = MatrixTransform::Identity();

	result.m[0][0] = (axis.x * axis.x) * (1 - cosAngle) + cosAngle;
	result.m[0][1] = (axis.x * axis.y) * (1 - cosAngle) - axis.z * sinAngle;
	result.m[0][2] = (axis.x * axis.z) * (1 - cosAngle) + axis.y * sinAngle;

	result.m[1][0] = (axis.x * axis.y) * (1 - cosAngle) + axis.z * sinAngle;
	result.m[1][1] = (axis.y * axis.y) * (1 - cosAngle) + cosAngle;
	result.m[1][2] = (axis.y * axis.z) * (1 - cosAngle) - axis.x * sinAngle;

	result.m[2][0] = (axis.x * axis.z) * (1 - cosAngle) - axis.y * sinAngle;
	result.m[2][1] = (axis.y * axis.z) * (1 - cosAngle) + axis.x * sinAngle;
	result.m[2][2] = (axis.z * axis.z) * (1 - cosAngle) + cosAngle;

	return result;
}

Matrix4x4 QuaternionTransform::MakeRotateAxisAngle(const Vector3& axis, float sin, float cos)
{
	Matrix4x4 result = MatrixTransform::Identity();
	result.m[0][0] = axis.x * axis.x * (1 - cos) + cos;
	result.m[0][1] = axis.x * axis.y * (1 - cos) - axis.z * sin;
	result.m[0][2] = axis.x * axis.z * (1 - cos) + axis.y * sin;
					  		   
	result.m[1][0] = axis.x * axis.y * (1 - cos) + axis.z * sin;
	result.m[1][1] = axis.y * axis.y * (1 - cos) + cos;
	result.m[1][2] = axis.y * axis.z * (1 - cos) - axis.x * sin;
					  		   
	result.m[2][0] = axis.x * axis.z * (1 - cos) - axis.y * sin;
	result.m[2][1] = axis.y * axis.z * (1 - cos) + axis.x * sin;
	result.m[2][2] = axis.z * axis.z * (1 - cos) + cos;
	return result;
}

Matrix4x4 QuaternionTransform::DirectionToDirection(const Vector3& from,const Vector3& to)
{
	Vector3 fromVec = VectorTransform::Normalize(from);
	Vector3 toVec = VectorTransform::Normalize(to);
	 Vector3 n = VectorTransform::Normalize(VectorTransform::Cross(fromVec, toVec));
	 
	 float cos = VectorTransform::Dot(fromVec, toVec);
	 float sin = VectorTransform::Length(VectorTransform::Cross(fromVec, toVec));

	 if (from.x == -to.x && from.y == -to.y && from.z == -to.z) 
	 {
		 if (from.x != 0.0f || from.y != 0.0f) 
		 {
			 n = { from.y,-from.x,0.0f };
		 }
		 else if (from.x != 0.0f || from.z != 0.0f) 
		 {
			 n = { from.z,0.0f,-from.x };
		 }
	 }

	 Matrix4x4 result{};

	 result = MakeRotateAxisAngle(n, sin, cos);

	return result;
}

float QuaternionTransform::Length(Quaternion q)
{
	float result{};
	result = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	return result;
}

Quaternion QuaternionTransform::Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result{};
	//result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	//result.x = lhs.y * rhs.z - lhs.z * rhs.y + rhs.w * lhs.x +lhs.w * rhs.x;
	//result.y = lhs.z * rhs.x - lhs.x * rhs.z + rhs.w * lhs.y +lhs.z * rhs.y;
	//result.z = lhs.x * rhs.y - lhs.y * rhs.x + rhs.z * lhs.w + lhs.z * rhs.w;
	lhs, rhs;
	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	result.x = lhs.y * rhs.z - lhs.z * rhs.y + rhs.w * lhs.x + lhs.w * rhs.x;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z + rhs.w * lhs.y + lhs.w * rhs.y;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x + rhs.w * lhs.z + lhs.w * rhs.z;
	return result;
}

Quaternion QuaternionTransform::IdentityQuaternion()
{
	return {0.0f,0.0f,0.0f,1.0f};
}

Quaternion QuaternionTransform::Conjugation(const Quaternion& quaternion)
{
	Quaternion result{};
	result.w = quaternion.w;
	result.x = -quaternion.x;
	result.y = -quaternion.y;
	result.z = -quaternion.z;
	return result;
}

float QuaternionTransform::Norm(const Quaternion& quaternion)
{
	float result{};

	result = sqrtf(
		quaternion.w * quaternion.w 
		+ quaternion.x * quaternion.x 
		+ quaternion.y * quaternion.y 
		+ quaternion.z * quaternion.z
	);
	return result;
}

Quaternion QuaternionTransform::Normalize(const Quaternion& quaternion)
{
	Quaternion result{};
	float length = Length(quaternion);
	if (length != 0.0f) {
		result.x = quaternion.x / length;
		result.y = quaternion.y / length;
		result.z = quaternion.z / length;
	}
	return result;
}

Quaternion QuaternionTransform::Inverse(const Quaternion& quaternion)
{
	Quaternion qC = Conjugation(quaternion);
	float norm = Norm(quaternion);
	float normxnorm = norm * norm;
	

	Quaternion result{};
	result.x = qC.x / normxnorm;
	result.y = qC.y / normxnorm;
	result.z = qC.z / normxnorm;
	result.w = qC.w / normxnorm;

	return result;
}
