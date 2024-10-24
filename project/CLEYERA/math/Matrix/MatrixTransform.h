#pragma once
#include"Pch.h"
#include"CreateResource.h"
#include"Vector/VectorTransform.h"
#include"Quaternion/QuaternionTransform.h"

namespace Math
{
	/// <summary>
	/// 行列
	/// </summary>
	namespace Matrix
	{
		/// <summary>
        /// 2つの行列を足し算する関数
        /// </summary>
		Matrix4x4 Add(Matrix4x4 m1, Matrix4x4 m2);

		/// <summary>
		/// 2つの行列を掛け算する関数
		/// </summary>
		Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

#pragma endregion

#pragma region 行列の変換

		/// <summary>
		/// 単位行列を返す関数
		/// </summary>
		Matrix4x4 Identity();

		/// <summary>
		/// 逆行列を計算する関数
		/// </summary>
		Matrix4x4 Inverse(Matrix4x4 m);

		/// <summary>
		/// 行列を転置する関数
		/// </summary>
		Matrix4x4 TransposeMatrix(const Matrix4x4& matrix);

		/// <summary>
		/// ビューポート行列を作成する関数
		/// </summary>
		Matrix4x4 ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

		/// <summary>
		/// コサインとサインの比を求める関数 (余接)
		/// </summary>
		/// <param name="theta">角度</param>
		/// <returns>余接</returns>
		float Cot(float theta);

		/// <summary>
		/// 透視投影行列を作成する関数
		/// </summary>
		Matrix4x4 PerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

		/// <summary>
		/// 正射影行列を作成する関数
		/// </summary>
		Matrix4x4 OrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

		/// <summary>
		/// スケール行列を作成する関数
		/// </summary>
		Matrix4x4 ScaleMatrix(Math::Vector::Vector3 s);

		/// <summary>
		/// 移動行列を作成する関数
		/// </summary>
		Matrix4x4 TranslateMatrix(Math::Vector::Vector3 t);

		/// <summary>
		/// X軸周りの回転行列を作成する関数
		/// </summary>
		Matrix4x4 RotateXMatrix(float theta);

		/// <summary>
		/// Y軸周りの回転行列を作成する関数
		/// </summary>
		Matrix4x4 RotateYMatrix(float theta);

		/// <summary>
		/// Z軸周りの回転行列を作成する関数
		/// </summary>
		Matrix4x4 RotateZMatrix(float theta);

		/// <summary>
		/// XYZ軸の回転を行う行列を作成する関数
		/// </summary>
		Matrix4x4 RotateXYZMatrix(float x, float y, float z);

		/// <summary>
		/// アフィン変換行列を作成する関数（スケール、回転、移動を含む）
		/// </summary>
		Matrix4x4 AffineMatrix(const Math::Vector::Vector3& Sv, const Math::Vector::Vector3& Rv, const Math::Vector::Vector3& Tv);

		/// <summary>
		/// アフィン変換行列を作成する関数（スケール、クォータニオンによる回転、移動を含む）
		/// </summary>
		Matrix4x4 AffineMatrix(const Math::Vector::Vector3& Sv, const Math::Qua::Quaternion& Rq, const Math::Vector::Vector3& Tv);

		/// <summary>
		/// 左手座標系での正射影行列を作成する関数
		/// </summary>
		Matrix4x4 OrthographicLH(float width, float height, float nearPlane, float farPlane);

		/// <summary>
		/// 左手座標系でのビュー行列を作成する関数（カメラの位置と注視点を指定）
		/// </summary>
		Matrix4x4 LookAtLH(Math::Vector::Vector3 eyePosition, Math::Vector::Vector3 focusPosition, Math::Vector::Vector3 upDirection);

		/// <summary>
		/// 任意の軸周りの回転行列を作成する関数
		/// </summary>
		Matrix4x4 RotateAxisAngle(const Math::Vector::Vector3& axis, float angle);

		/// <summary>
		/// サインとコサインを使った任意の軸周りの回転行列を作成する関数
		/// </summary>
		Matrix4x4 RotateAxisAngle(const Math::Vector::Vector3& axis, float sin, float cos);

		/// <summary>
		/// 2つの方向ベクトル間の回転行列を作成する関数
		/// </summary>
		Matrix4x4 DirectionToDirection(const Math::Vector::Vector3& from, const Math::Vector::Vector3& to);

		/// <summary>
		/// 2つの行列をスケール行列として合成する関数
		/// </summary>
		Matrix4x4 ScaleMatrixByAnother(Math::Matrix::Matrix4x4 A, const Math::Matrix::Matrix4x4 B);


	}

};
