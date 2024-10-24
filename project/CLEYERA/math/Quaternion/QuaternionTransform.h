#pragma once

#include"Vector/VectorTransform.h"
#include"Matrix/MatrixTransform.h"
#include"Quaternion/Quaternion.h"


namespace Math
{
	/// <summary>
	/// �l����
	/// </summary>
	namespace Qua
	{
		/// <summary>
	    /// �N�H�[�^�j�I���̒������v�Z����֐�
		/// </summary>
		float Length(Quaternion q);

		/// <summary>
		/// 2�̃N�H�[�^�j�I�����|���Z����֐�
		/// </summary>
		Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

		/// <summary>
		/// �P�ʃN�H�[�^�j�I����Ԃ��֐�
		/// </summary>
		Quaternion IdentityQuaternion();

		/// <summary>
		/// �N�H�[�^�j�I���̋������v�Z����֐�
		/// </summary>
		Quaternion Conjugation(const Quaternion& quaternion);

		/// <summary>
		/// �N�H�[�^�j�I���̃m�����i�傫���j���v�Z����֐�
		/// </summary>
		float Norm(const Quaternion& quaternion);

		/// <summary>
		/// �N�H�[�^�j�I���𐳋K������֐�
		/// </summary>
		Quaternion Normalize(const Quaternion& quaternion);

		/// <summary>
		/// �N�H�[�^�j�I���̋t�����v�Z����֐�
		/// </summary>
		Quaternion Inverse(const Quaternion& quaternion);

		/// <summary>
		/// 2�̃N�H�[�^�j�I���̃h�b�g�ς��v�Z����֐�
		/// </summary>
		float Dot(const Quaternion& q1, const Quaternion& q2);

		/// <summary>
		/// �N�H�[�^�j�I�����g�p���ăx�N�g������]������֐�
		/// </summary>
		Math::Vector::Vector3 RotateVector(const Math::Vector::Vector3& v, const Quaternion& q);

		/// <summary>
		/// 2�̃N�H�[�^�j�I���Ԃŋ��ʐ��`��� (Slerp) ���s���֐�
		/// </summary>
		Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

		/// <summary>
		///�@��]�֐�
		/// </summary>
		Math::Matrix::Matrix4x4 RotateMatrix(const Quaternion& q); 
	}

};

