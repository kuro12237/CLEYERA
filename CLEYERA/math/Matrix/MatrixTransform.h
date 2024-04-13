#pragma once
#include"Pch.h"
#include"CreateResource.h"
#include"Vector/VectorTransform.h"

namespace Math
{
	namespace Matrix
	{

		/// <summary>
		/// 足し算
		/// </summary>
		Matrix4x4 Add(Matrix4x4 m1, Matrix4x4 m2);

		/// <summary>
		/// 掛け算
		/// </summary>
		Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

#pragma endregion

#pragma region 行列の変換
		/// <summary>
		/// 初期化 
		/// </summary>
		Matrix4x4 Identity();

		/// <summary>
		/// 逆行列
		/// </summary>
		Matrix4x4 Inverse(Matrix4x4 m);

		/// <summary>
		/// 射影行列
		/// </summary>
		Matrix4x4 ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

		/// <summary>
		/// 余接
		/// </summary>
		/// <param name="theta"></param>
		/// <returns></returns>
		float Cot(float theta);

		/// <summary>
		/// 透視投影行列
		/// </summary>
		Matrix4x4 PerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

		/// <summary>
		/// 正射影行列
		/// </summary>
		Matrix4x4 OrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip);

		/// <summary>
		/// 
		/// </summary>
		Matrix4x4 ScaleMatrix(Math::Vector::Vector3 s);

		/// <summary>
		/// 移動行列
		/// </summary>
		Matrix4x4 TranslateMatrix(Math::Vector::Vector3 t);

		/// <summary>
		/// Xを軸とした回転
		/// </summary>
		Matrix4x4 RotateXMatrix(float theta);

		/// <summary>
		/// Yを軸とした回転
		/// </summary>
		Matrix4x4 RotateYMatrix(float theta);

		/// <summary>
		/// Xを軸とした回転
		/// </summary>
		Matrix4x4 RotateZMatrix(float theta);

		/// <summary>
		/// x,y,zすべての回転
		/// </summary>
		Matrix4x4 RotateXYZMatrix(float x, float y, float z);

		/// <summary>
		/// アフィン変換
		/// </summary>
		/// <param name="大きさ"></param>
		/// <param name="回転"></param>
		/// <param name="移動"></param>
		Matrix4x4 AffineMatrix(const Math::Vector::Vector3& Sv, const Math::Vector::Vector3& Rv, const Math::Vector::Vector3& Tv);

		Matrix4x4 OrthographicLH(float width, float height, float nearPlane, float farPlane);
		Matrix4x4 LookAtLH(Math::Vector::Vector3 eyePosition, Math::Vector::Vector3 focusPosition, Math::Vector::Vector3 upDirection);

		Matrix4x4 RotateAxisAngle(const Math::Vector::Vector3& axis, float angle);

		Matrix4x4 RotateAxisAngle(const Math::Vector::Vector3& axis, float sin, float cos);

		Matrix4x4 DirectionToDirection(const Math::Vector::Vector3& from, const Math::Vector::Vector3& to);

        #pragma endregion
	}

};
