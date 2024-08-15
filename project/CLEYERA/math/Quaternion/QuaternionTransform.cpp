#include "QuaternionTransform.h"

using namespace Math::Vector;
using namespace Math::Matrix;
using namespace  Math::Qua;

float Math::Qua::Length(Quaternion q)
{
	float result{};
	result = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	return result;
}

Quaternion Math::Qua::Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result{};
	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	result.x = lhs.y * rhs.z - lhs.z * rhs.y + rhs.w * lhs.x + lhs.w * rhs.x;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z + rhs.w * lhs.y + lhs.w * rhs.y;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x + rhs.w * lhs.z + lhs.w * rhs.z;
	return result;
}

Quaternion Math::Qua::IdentityQuaternion()
{
	return { 0.0f,0.0f,0.0f,1.0f };
}

Quaternion Math::Qua::Conjugation(const Quaternion& quaternion)
{
	Quaternion result{};
	result.w = quaternion.w;
	result.x = -quaternion.x;
	result.y = -quaternion.y;
	result.z = -quaternion.z;
	return result;
}

float Math::Qua::Norm(const Quaternion& quaternion)
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

Quaternion Math::Qua::Normalize(const Quaternion& quaternion)
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

Quaternion Math::Qua::Inverse(const Quaternion& quaternion)
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

float Math::Qua::Dot(const Quaternion& q1, const Quaternion& q2)
{
	return float(q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);
}

Vector3 Math::Qua::RotateVector(const Vector3& v, const Quaternion& q)
{
	Quaternion vecQuat{};
	vecQuat.w = 0.0f;
	vecQuat.x = v.x;
	vecQuat.y = v.y;
	vecQuat.z = v.z;

	Quaternion conjugate = Conjugation(q);

	// ベクトルを回転する
	Quaternion rotatedVec = Multiply(q, Multiply(vecQuat, conjugate));

	// 回転後のベクトルを抽出して返す
	return { rotatedVec.x, rotatedVec.y, rotatedVec.z };

}

Quaternion Math::Qua::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
{
	// クォータニオンの内積を計算
	float dot = Dot(q1, q2);

	Quaternion qn1 = q1;
	Quaternion qn2 = q2;

	if (dot < 0.0f)
	{
		qn1 = { -qn1.x,-qn1.y,-qn1.z,-qn1.w };
		dot = -dot;
	}
	if (dot >= 1.0f - std::numeric_limits<float>::epsilon())
	{
		float timer = 1.0f - t;
		return Math::Qua::Quaternion{
			timer * qn1.x + t * qn1.x,
            timer * qn1.y + t * qn1.y,
            timer * qn1.z + t * qn1.z,
            timer * qn1.w + t * qn1.w,

		};
	}

	// q1とq2の間の角度を計算
	float theta = std::acos(dot);

	float sinTheta = std::sin(theta);
	float scale0 = std::sin((1 - t) * theta) / sinTheta;
	float scale1 = std::sin(t * theta) / sinTheta;

	// 補間されたクォータニオンを計算して返す
	return Quaternion(
		scale0 * qn1.x + scale1 * qn2.x,
		scale0 * qn1.y + scale1 * qn2.y,
		scale0 * qn1.z + scale1 * qn2.z,
		scale0 * qn1.w + scale1 * qn2.w
	);
}

Matrix4x4 Math::Qua::RotateMatrix(const Quaternion& q)
{
	Matrix4x4 result = Identity();

	result.m[0][0] = (q.w * q.w) + (q.x * q.x) - (q.y * q.y) - (q.z * q.z);
	result.m[0][1] = 2.0f * ((q.x * q.y) + (q.w * q.z));
	result.m[0][2] = 2.0f * ((q.x * q.z) - (q.w * q.y));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 2.0f * ((q.x * q.y) - (q.w * q.z));
	result.m[1][1] = (q.w * q.w) - (q.x * q.x) + (q.y * q.y) - (q.z * q.z);
	result.m[1][2] = 2.0f * ((q.y * q.z) + (q.w * q.x));
	result.m[1][3] = 0.0f;

	result.m[2][0] = 2.0f * ((q.x * q.z) + (q.w * q.y));
	result.m[2][1] = 2.0f * ((q.y * q.z) - (q.w * q.x));
	result.m[2][2] = (q.w * q.w) - (q.x * q.x) - (q.y * q.y) + (q.z * q.z);
	result.m[2][3] = 0.0f;

	return result;
}

