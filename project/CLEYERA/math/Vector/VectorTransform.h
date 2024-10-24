#pragma once
#include"Pch.h"

namespace Math
{
	/// <summary>
	/// �x�N�g��
	/// </summary>
	namespace Vector
	{
		/// <summary>
        /// �x���@�̊p�x�����W�A���ɕϊ�����֐�
        /// </summary>
		float degreesToRadians(float degrees);

		/// <summary>
		/// 2�����x�N�g���̒������v�Z����֐�
		/// </summary>
		float Length(const Vector2& v);

		/// <summary>
		/// 3�����x�N�g���̒������v�Z����֐�
		/// </summary>
		float Length(const Vector3& v);

		/// <summary>
		/// 2��3�����x�N�g�������Z����֐�
		/// </summary>
		Vector3 Add(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// 2��3�����x�N�g�������Z����֐�
		/// </summary>
		Vector3 Subtruct(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// 3�����x�N�g���ƃX�J���[�l���|���Z����֐�
		/// </summary>
		Vector3 Multiply(const Vector3& v1, const float& v2);

		/// <summary>
		/// 2��3�����x�N�g����v�f���ƂɊ|���Z����֐�
		/// </summary>
		Vector3 Multiply(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// 2�����x�N�g���ƃX�J���[�l���|���Z����֐�
		/// </summary>
		Vector2 Multiply(const Vector2& v1, const float v);

		/// <summary>
		/// 3�����x�N�g����4x4�s��ŕϊ�����֐�
		/// </summary>
		Vector3 TransformNormal(const Vector3& v, const Math::Matrix::Matrix4x4& m);

		/// <summary>
		/// �l�𐳋K������֐�
		/// </summary>
		float Normalize(const float& v);

		/// <summary>
		/// 2�����x�N�g���𐳋K������֐�
		/// </summary>
		Vector2 Normalize(const Vector2& v);

		/// <summary>
		/// 3�����x�N�g���𐳋K������֐�
		/// </summary>
		Vector3 Normalize(const Vector3& v);

		/// <summary>
		/// ���`��Ԃ��s���֐�
		/// </summary>
		float Lerp(const float& a, const float& b, const float t);

		/// <summary>
		/// 3�����x�N�g������`��Ԃ���֐�
		/// </summary>
		Vector3 Lerp(const Vector3& a, const Vector3& b, const float t);

		/// <summary>
		/// 2��3�����x�N�g���̃h�b�g�ς��v�Z����֐�
		/// </summary>
		float Dot(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// ���ʐ��`��Ԃ��s���֐�
		/// </summary>
		Vector3 SlerpFanc(Vector3 start, Vector3 end, float t);

		/// <summary>
		/// 2��4�����x�N�g�������Z����֐�
		/// </summary>
		Vector4 Subtruct(const Vector4& v1, const Vector4& v2);

		/// <summary>
		/// 2��3�����x�N�g���̃N���X�ς��v�Z����֐�
		/// </summary>
		Vector3 Cross(const Vector3 v1, const Vector3 v2);

		/// <summary>
		/// 3�����x�N�g�����s��ŕϊ�����֐�
		/// </summary>
		Vector3 TransformByMatrix(const Vector3 vector, const Math::Matrix::Matrix4x4 matrix);

		/// <summary>
		/// Ease Out Bounce �̕�Ԋ֐�
		/// </summary>
		float easeOutBounce(float t);

		/// <summary>
		/// Ease Out Sine �̕�Ԋ֐�
		/// </summary>
		float easeOutSine(float t);

		/// <summary>
		/// Ease In Sine �̕�Ԋ֐�
		/// </summary>
		float easeInSine(float t);

		/// <summary>
		/// 3�����x�N�g����X����]���v�Z����֐�
		/// </summary>
		float CalcXRotation(const Vector3& rotate);

		/// <summary>
		/// 3�����x�N�g����Y����]���v�Z����֐�
		/// </summary>
		float CalcYRotation(const Vector3& rotate);

		/// <summary>
		/// Ease Out Sine �Ɋ�Â����`��Ԃ��s���֐�
		/// </summary>
		Vector3 LerpEaseOutSine(const Vector3& a, const Vector3& b, const float t);

		/// <summary>
		/// Ease In Sine �Ɋ�Â����`��Ԃ��s���֐�
		/// </summary>
		Vector3 LerpEaseInSine(const Vector3& a, const Vector3& b, const float t);

		/// <summary>
		/// Ease Out Sine �Ɋ�Â��X�J���[�l�̐��`��Ԃ��s���֐�
		/// </summary>
		float LerpEaseOutSine(const float& a, const float& b, const float t);

		/// <summary>
		/// Ease In Sine �Ɋ�Â��X�J���[�l�̐��`��Ԃ��s���֐�
		/// </summary>
		float LerpEaseInSine(const float& a, const float& b, const float t);

		/// <summary>
		/// Ease Out Expo �̕�Ԋ֐��i�e���v���[�g�j
		/// </summary>
		template<typename T>
		T easeOutExpo(const T& a, const T& b, const float t)
		{
			T result;
			float easeT = t == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * t);
			result = a + easeT * (b - a);
			return result;
		}

		/// <summary>
		/// Ease Out Quad �̕�Ԋ֐��i�e���v���[�g�j
		/// </summary>
		template<typename T>
		T EaseOutQuad(const T& start, const T& end, float t) {
			// EaseOutQuad�̕�Ԍv�Z
			t = 1 - (1 - t) * (1 - t);

			// start��end�̊Ԃ�t�ɉ����ĕ��
			return start + t * (end - start);
		}

		/// <summary>
		/// Catmull-Rom ��Ԃ��s���֐�
		/// </summary>
		Vector3 Catmull_Rom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t);

	}
};

