#pragma once

#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"

#include"../Matrix/Matrix2x2.h"
#include"../Matrix/Matrix3x3.h"
#include"../Matrix/Matrix4x4.h"

#include<cassert>

class VectorTransform
{
public:
	VectorTransform();
	~VectorTransform();


#pragma region 二次元

#pragma region+=*
	/// <summary>
	/// 二次元ベクトルの足し算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector2 Add(Vector2 v1, Vector2 v2);

	/// <summary>
	/// 二次元ベクトルの引き算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector2 Subtract(Vector2 v1, Vector2 v2);

	/// <summary>
	/// 二次元ベクトルの掛け算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector2 Multiply(Vector2 v1, Vector2 v2);

	/// <summary>
	/// 二次元ベクトルの割り算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector2 Divide(Vector2 v1, Vector2 v2);
	

	/// <summary>
	/// 二次元ベクトルと2x2行列の掛け算
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);

#pragma endregion

#pragma endregion


#pragma region 三次元
#pragma region+=*
	/// <summary>
    /// 三次元ベクトルの足し算
    /// </summary>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    /// <returns></returns>
	Vector3 Add(Vector3 v1, Vector3 v2);

	/// <summary>
	/// 三次元ベクトルの引き算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector3 Subtract(Vector3 v1, Vector3 v2);


	/// <summary>
	/// 三次元ベクトルの掛け算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector3 Multiply(Vector3 v1, Vector3 v2);

	/// <summary>
	/// 三次元ベクトルの割り算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector3 Divide(Vector3 v1, Vector3 v2);


	/// <summary>
	/// 三次元ベクトルと3x3行列の掛け算
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector3 Multiply(Vector3 v, Matrix3x3 matrix);

#pragma endregion
#pragma endregion

#pragma region 四次元
#pragma region+=*
	/// <summary>
	/// 四次元ベクトルの足し算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector4 Add(Vector4 v1, Vector4 v2);

	/// <summary>
	/// 四次元ベクトルの引き算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector4 Subtract(Vector4 v1, Vector4 v2);


	/// <summary>
	/// 四次元ベクトルの掛け算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector4 Multiply(Vector4 v1, Vector4 v2);

	/// <summary>
	/// 四次元ベクトルの割り算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector4 Divide(Vector4 v1, Vector4 v2);


	/// <summary>
	/// 四次元ベクトルと2x2行列の掛け算
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector4 Multiply(Vector4 v, Matrix4x4 matrix);


	/// <summary>
	/// 向き
	/// </summary>
	/// <param name="v"></param>
	/// <param name="m"></param>
	/// <returns></returns>
	Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
#pragma endregion



#pragma region 

private:

};

