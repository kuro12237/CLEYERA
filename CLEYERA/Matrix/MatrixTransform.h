#pragma once

///ベクトル
#include"../Vector/Vector2.h"
#include"../Vector/Vector3.h"
#include"../Vector/Vector4.h"

///行列
#include"Matrix2x2.h"
#include"Matrix3x3.h"
#include"Matrix4x4.h"

#include<cmath>


#include <cassert>

class MatrixTransform
{
public:
	MatrixTransform();
	~MatrixTransform();
	
	//
	//二次元行列
	//
#pragma region 二次元行列

#pragma region +-*
	
	/// <summary>
	/// 2x2行列の足し算
	/// </summary>
	/// <param name="matrix1"></param>
	/// <param name="matrix2"></param>
	/// <returns></returns>
	Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);

	/// <summary>
	/// 2x2行列の引き算
	/// </summary>
	/// <param name="matrix1"></param>
	/// <param name="matrix2"></param>
	/// <returns></returns>
	Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);

	/// <summary>
	/// 2x2行列の掛け算
	/// </summary>
	/// <param name="matrix1"></param>
	/// <param name="matrix2"></param>
	/// <returns></returns>
	Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);

	
#pragma endregion



#pragma region 回転

	/// <summary>
	/// 回転
	/// </summary>
	/// <param name="thata"></param>
	/// <returns></returns>
	Matrix2x2 MakeRotate2x2Matrix(float theta);

#pragma endregion 

#pragma region 行列の変換

	/// <summary>
	/// 2x2の逆行列
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Matrix2x2 Inverse(Matrix2x2 matrix);


	/// <summary>
	/// 2x2の転置行列
    /// </summary>
    /// <param name="matrix"></param>
    /// <returns></returns>
	Matrix2x2 Transpose(Matrix2x2 matrix);

#pragma endregion

#pragma endregion

	//三次元行列
#pragma region 三次元行列
#pragma region +-*

	/// <summary>
	/// 3x3行列の足し算
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix3x3 Add(const Matrix3x3& m1, const Matrix3x3& m2);
	
	/// <summary>
	/// 3x3行列の引き算
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix3x3 Subract(const Matrix3x3& m1, const Matrix3x3& m2);


	/// <summary>
	/// 3x3行列の掛け算
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix3x3 Multiply(const Matrix3x3& m1, const Matrix3x3& m2);


#pragma endregion 
 
#pragma region 移動・回転・大きさ



	/// <summary>
	/// 3x3行列の平行移動
	/// </summary>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix3x3 MakeTranslate3x3Matrix(Vector2 translate);

	/// <summary>
	/// 3x3行列回転
	/// </summary>
	/// <param name="theta"></param>
	/// <returns></returns>
	Matrix3x3 MakeRotate3x3Matrix(float radian);

	/// <summary>
	/// 3x3行列の大きさ
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Matrix3x3 MakeScaleMatrix(const Vector2 scale);



#pragma endregion

#pragma region 行列の変換

	/// <summary>
	/// 3x3のアフィン変換
	/// </summary>
	/// <param name="translate"></param>
	/// <param name="radian"></param>
	/// <param name="scale"></param>
	/// <returns></returns>
	Matrix3x3 MakeAffineMatrix(const Vector2 translate, float radian, const Vector2 scale);


	/// <summary>
	/// 2次元ベクトルを3x3行列で変換
	/// </summary>
	/// <param name="v"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector2 Transform(Vector2 v, Matrix3x3 matrix);

	/// <summary>
	/// 3x3の逆行列
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Matrix3x3 Inverse(Matrix3x3 matrix);

	/// <summary>
	/// 3x3の転置行列
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Matrix3x3 Transpose(Matrix3x3 matrix);

	/// <summary>
	/// 3x3の正射影行列
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="right"></param>
	/// <param name="bottom"></param>
	/// <returns></returns>
	Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

	/// <summary>
	/// 3x3ビューポート行列
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	Matrix3x3 MakeviewportMatrix(float left, float top, float width, float height);
#pragma endregion


#pragma endregion	
	
	//
	///四次元行列
	//
#pragma region 三次元行列

#pragma region +-*

    /// <summary>
    /// 4x4行列の足し算
    /// </summary>
    /// <param name="m1"></param>
    /// <param name="m2"></param>
    /// <returns></returns>
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 4x4行列の引き算
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Subract(const Matrix4x4& m1, const Matrix4x4& m2);


	/// <summary>
	/// 4x4行列の乗算
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);
#pragma endregion 

#pragma region 行列の移動・大きさ・回転
	/// <summary>
	/// 4x4スケール行列
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Matrix4x4 MakeScaleMatrix(const Vector3 scale);

	/// <summary>
	/// 4x4平行移動行列
	/// </summary>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix4x4 MakeTranslateMatrix(Vector3 translate);

#pragma region 回転
	/// <summary>
	/// 4x4Y軸の回転
	/// </summary>
	/// <param name="角度"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// 4x4X軸の回転
	/// </summary>
	/// <param name="角度"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// 4x4Z軸の回転
	/// </summary>
	/// <param name="角度"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateZMatrix(float radian);


	/// <summary>
	/// XYZすべての回転
	/// </summary>
	/// <param name="Xradian"></param>
	/// <param name="Yradian"></param>
	/// <param name="Zradian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXYZMatrix(float Xradian, float radianY, float Zradian);
#pragma endregion

#pragma endregion

#pragma region 行列の変換

	/// <summary>
	/// 4x4アフィン変換行列
	/// </summary>
	/// <param name="scale"></param>
	/// <param name="rotate"></param>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);


	/// <summary>
	/// 4x4転換行列
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	Matrix4x4 Transpose(const Matrix4x4 m);

	/// <summary>
	/// 4x4逆行列
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Matrix4x4 Inverse(Matrix4x4& matrix);

	/// <summary>
	/// 4x4単位行列
	/// </summary>
	/// <returns></returns>
	Matrix4x4 Identity();


	/// <summary>
	/// 4x4正射影行列
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="right"></param>
	/// <param name="bottom"></param>
	/// <param name="neaCrlip"></param>
	/// <param name="farClip"></param>
	/// <returns></returns>
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip);
	
	/// <summary>
	/// 4x4ビューポート行列
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="minDepth"></param>
	/// <param name="maxDepth"></param>
	/// <returns></returns>
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	/// <summary>
	/// 余接
	/// </summary>
	/// <param name="theta"></param>
	/// <returns></returns>
	static float Cot(float theta);

	/// <summary>
	/// 透視投影行列
	/// </summary>
	/// <param name="fovY"></param>
	/// <param name="aspectRatio"></param>
	/// <param name="nearClip"></param>
	/// <param name="farClip"></param>
	/// <returns></returns>
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
	
#pragma endregion 

#pragma endregion



};

