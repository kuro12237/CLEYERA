#pragma once
#include "Pch.h"

// 球
struct Sphere {
	Math::Vector::Vector3 center;
	float radius;
};


// 直線
struct Line {
	Math::Vector::Vector3 origin;	// !< 始点
	Math::Vector::Vector3 diff;   // !< 終点への差分ベクトル
};


// 半直線
struct Ray {
	Math::Vector::Vector3 origin;	// !< 始点
	Math::Vector::Vector3 diff;   // !< 終点への差分ベクトル
};


// 線分
struct Segment {
	Math::Vector::Vector3 origin;	// !< 始点
	Math::Vector::Vector3 diff;   // !< 終点への差分ベクトル
};


// 平面
struct Plane {
	Math::Vector::Vector3 normal;	// !< 法線
	float distance; // !< 距離
};


// 三角形
struct Triangle {
	Math::Vector::Vector3 vertices[3]; // !< 頂点
};


// AABB
struct AABB {
	Math::Vector::Vector3 min = { -0.5f,-0.5f,-0.5f }; // !< 最少点
	Math::Vector::Vector3 max = { 0.5f,0.5f,0.5f }; // !< 最大点
};


// OBB
struct OBB {
	Math::Vector::Vector3 center;			   // !< 中心点
	Math::Vector::Vector3 orientations[3]{}; // !< 座標軸。正規化・直交必須
	Math::Vector::Vector3 halfSize;          // !< 座標軸方向の長さの半分。中心から面までの距離
};