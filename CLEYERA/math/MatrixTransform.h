#pragma once
#include"Pch.h"
#include"CreateResource.h"
#include"VectorTransform.h"

class MatrixTransform
{
public:


#pragma region 

	/// <summary>
	/// 足し算
	/// </summary>
	static Matrix4x4 Add(Matrix4x4 m1, Matrix4x4 m2);

	/// <summary>
	/// 掛け算
	/// </summary>
	static Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);
	
#pragma endregion

#pragma region 行列の変換
	/// <summary>
	/// 初期化 
	/// </summary>
	static Matrix4x4 Identity();

	/// <summary>
	/// 逆行列
	/// </summary>
	static Matrix4x4 Inverse(Matrix4x4 m);
	
	/// <summary>
	/// 射影行列
	/// </summary>
	static Matrix4x4 ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
	
	/// <summary>
    /// 余接
    /// </summary>
    /// <param name="theta"></param>
    /// <returns></returns>
	static float Cot(float theta);

	/// <summary>
	/// 透視投影行列
	/// </summary>
	static Matrix4x4 PerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
	
	/// <summary>
	/// 正射影行列
	/// </summary>
	static Matrix4x4 OrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip);

	/// <summary>
	/// 
	/// </summary>
	static Matrix4x4 ScaleMatrix(Vector3 s);
	
	/// <summary>
	/// 移動行列
	/// </summary>
	static Matrix4x4 TranslateMatrix(Vector3 t);

	/// <summary>
	/// Xを軸とした回転
	/// </summary>
	static Matrix4x4 RotateXMatrix(float theta);
	
	/// <summary>
	/// Yを軸とした回転
	/// </summary>
	static Matrix4x4 RotateYMatrix(float theta);

	/// <summary>
	/// Xを軸とした回転
	/// </summary>
	static Matrix4x4 RotateZMatrix(float theta);

	/// <summary>
	/// x,y,zすべての回転
	/// </summary>
	static Matrix4x4 RotateXYZMatrix(float x, float y, float z);

	/// <summary>
	/// アフィン変換
	/// </summary>
	/// <param name="大きさ"></param>
	/// <param name="回転"></param>
	/// <param name="移動"></param>
	static Matrix4x4 AffineMatrix(const Vector3& Sv, const Vector3& Rv, const Vector3& Tv);


	static Matrix4x4 OrthographicLH(float width, float height, float nearPlane, float farPlane);
	static Matrix4x4 LookAtLH(Vector3 eyePosition, Vector3 focusPosition, Vector3 upDirection);

#pragma endregion
private:

};
