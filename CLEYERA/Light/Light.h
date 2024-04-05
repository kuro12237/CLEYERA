#pragma once
#include"Pch.h"
#include"CreateResource.h"
#include"MatrixTransform.h"

struct PointLight_param
{
	Vector4 color = {1.0f,1.0f,1.0f,1.0f};
	Vector3 position = {0.0f,0.0f,0.0f};
	/// <summary>
	/// 強さ
	/// </summary>
	float intencity = 1.0f;
	/// <summary>
	/// 最大半径
	/// </summary>
	float radious = 1.0f;
	/// <summary>
	/// 減衰率
	/// </summary>
	float decay = 0.1f;

	Vector3 worldPos_ = {};

	void UpdateMatrix();

};
