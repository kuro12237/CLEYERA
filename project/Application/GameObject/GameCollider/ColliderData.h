#pragma once
#include"../../../CLEYERA/math/Vector/VectorTransform.h"

/// <summary>
/// 箱の当たり判定データ
/// </summary>
struct AABB
{
	Math::Vector::Vector3 min;
	Math::Vector::Vector3 max;
};
