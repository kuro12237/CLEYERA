#pragma once

#include"Vector/VectorTransform.h"
#include"Matrix/MatrixTransform.h"
#include"Quaternion/Quaternion.h"


namespace Math
{
	/// <summary>
	/// 四元数
	/// </summary>
	namespace Qua
	{
		/// <summary>
	    /// クォータニオンの長さを計算する関数
		/// </summary>
		float Length(Quaternion q);

		/// <summary>
		/// 2つのクォータニオンを掛け算する関数
		/// </summary>
		Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

		/// <summary>
		/// 単位クォータニオンを返す関数
		/// </summary>
		Quaternion IdentityQuaternion();

		/// <summary>
		/// クォータニオンの共役を計算する関数
		/// </summary>
		Quaternion Conjugation(const Quaternion& quaternion);

		/// <summary>
		/// クォータニオンのノルム（大きさ）を計算する関数
		/// </summary>
		float Norm(const Quaternion& quaternion);

		/// <summary>
		/// クォータニオンを正規化する関数
		/// </summary>
		Quaternion Normalize(const Quaternion& quaternion);

		/// <summary>
		/// クォータニオンの逆数を計算する関数
		/// </summary>
		Quaternion Inverse(const Quaternion& quaternion);

		/// <summary>
		/// 2つのクォータニオンのドット積を計算する関数
		/// </summary>
		float Dot(const Quaternion& q1, const Quaternion& q2);

		/// <summary>
		/// クォータニオンを使用してベクトルを回転させる関数
		/// </summary>
		Math::Vector::Vector3 RotateVector(const Math::Vector::Vector3& v, const Quaternion& q);

		/// <summary>
		/// 2つのクォータニオン間で球面線形補間 (Slerp) を行う関数
		/// </summary>
		Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

		/// <summary>
		///　回転関数
		/// </summary>
		Math::Matrix::Matrix4x4 RotateMatrix(const Quaternion& q); 
	}

};

