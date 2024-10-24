#pragma once
#include"Pch.h"

namespace Math
{
	/// <summary>
	/// ベクトル
	/// </summary>
	namespace Vector
	{
		/// <summary>
        /// 度数法の角度をラジアンに変換する関数
        /// </summary>
		float degreesToRadians(float degrees);

		/// <summary>
		/// 2次元ベクトルの長さを計算する関数
		/// </summary>
		float Length(const Vector2& v);

		/// <summary>
		/// 3次元ベクトルの長さを計算する関数
		/// </summary>
		float Length(const Vector3& v);

		/// <summary>
		/// 2つの3次元ベクトルを加算する関数
		/// </summary>
		Vector3 Add(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// 2つの3次元ベクトルを減算する関数
		/// </summary>
		Vector3 Subtruct(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// 3次元ベクトルとスカラー値を掛け算する関数
		/// </summary>
		Vector3 Multiply(const Vector3& v1, const float& v2);

		/// <summary>
		/// 2つの3次元ベクトルを要素ごとに掛け算する関数
		/// </summary>
		Vector3 Multiply(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// 2次元ベクトルとスカラー値を掛け算する関数
		/// </summary>
		Vector2 Multiply(const Vector2& v1, const float v);

		/// <summary>
		/// 3次元ベクトルを4x4行列で変換する関数
		/// </summary>
		Vector3 TransformNormal(const Vector3& v, const Math::Matrix::Matrix4x4& m);

		/// <summary>
		/// 値を正規化する関数
		/// </summary>
		float Normalize(const float& v);

		/// <summary>
		/// 2次元ベクトルを正規化する関数
		/// </summary>
		Vector2 Normalize(const Vector2& v);

		/// <summary>
		/// 3次元ベクトルを正規化する関数
		/// </summary>
		Vector3 Normalize(const Vector3& v);

		/// <summary>
		/// 線形補間を行う関数
		/// </summary>
		float Lerp(const float& a, const float& b, const float t);

		/// <summary>
		/// 3次元ベクトルを線形補間する関数
		/// </summary>
		Vector3 Lerp(const Vector3& a, const Vector3& b, const float t);

		/// <summary>
		/// 2つの3次元ベクトルのドット積を計算する関数
		/// </summary>
		float Dot(const Vector3& v1, const Vector3& v2);

		/// <summary>
		/// 球面線形補間を行う関数
		/// </summary>
		Vector3 SlerpFanc(Vector3 start, Vector3 end, float t);

		/// <summary>
		/// 2つの4次元ベクトルを減算する関数
		/// </summary>
		Vector4 Subtruct(const Vector4& v1, const Vector4& v2);

		/// <summary>
		/// 2つの3次元ベクトルのクロス積を計算する関数
		/// </summary>
		Vector3 Cross(const Vector3 v1, const Vector3 v2);

		/// <summary>
		/// 3次元ベクトルを行列で変換する関数
		/// </summary>
		Vector3 TransformByMatrix(const Vector3 vector, const Math::Matrix::Matrix4x4 matrix);

		/// <summary>
		/// Ease Out Bounce の補間関数
		/// </summary>
		float easeOutBounce(float t);

		/// <summary>
		/// Ease Out Sine の補間関数
		/// </summary>
		float easeOutSine(float t);

		/// <summary>
		/// Ease In Sine の補間関数
		/// </summary>
		float easeInSine(float t);

		/// <summary>
		/// 3次元ベクトルのX軸回転を計算する関数
		/// </summary>
		float CalcXRotation(const Vector3& rotate);

		/// <summary>
		/// 3次元ベクトルのY軸回転を計算する関数
		/// </summary>
		float CalcYRotation(const Vector3& rotate);

		/// <summary>
		/// Ease Out Sine に基づく線形補間を行う関数
		/// </summary>
		Vector3 LerpEaseOutSine(const Vector3& a, const Vector3& b, const float t);

		/// <summary>
		/// Ease In Sine に基づく線形補間を行う関数
		/// </summary>
		Vector3 LerpEaseInSine(const Vector3& a, const Vector3& b, const float t);

		/// <summary>
		/// Ease Out Sine に基づくスカラー値の線形補間を行う関数
		/// </summary>
		float LerpEaseOutSine(const float& a, const float& b, const float t);

		/// <summary>
		/// Ease In Sine に基づくスカラー値の線形補間を行う関数
		/// </summary>
		float LerpEaseInSine(const float& a, const float& b, const float t);

		/// <summary>
		/// Ease Out Expo の補間関数（テンプレート）
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
		/// Ease Out Quad の補間関数（テンプレート）
		/// </summary>
		template<typename T>
		T EaseOutQuad(const T& start, const T& end, float t) {
			// EaseOutQuadの補間計算
			t = 1 - (1 - t) * (1 - t);

			// startとendの間でtに応じて補間
			return start + t * (end - start);
		}

		/// <summary>
		/// Catmull-Rom 補間を行う関数
		/// </summary>
		Vector3 Catmull_Rom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t);

	}
};

