#pragma once

#include"Vector/VectorTransform.h"
#include"Matrix/MatrixTransform.h"
#include"Quaternion/Quaternion.h"


namespace Math
{
	namespace Qua
	{
		float Length(Quaternion q);

		Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

		Quaternion IdentityQuaternion();

		Quaternion Conjugation(const Quaternion& quaternion);

		float Norm(const Quaternion& quaternion);

		Quaternion Normalize(const Quaternion& quaternion);

		Quaternion Inverse(const Quaternion& quaternion);

		float Dot(const Quaternion& q1, const Quaternion& q2);

		Math::Vector::Vector3 RotateVector(const Math::Vector::Vector3& v, const Quaternion& q);

		Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

		Math::Matrix::Matrix4x4 RotateMatrix(const Quaternion& q);
	}

};

