#pragma once
#include "Vector3.h"

// 球
struct Sphere {
	Vector3 center;
	float radius;
};


// 直線
struct Line {
	Vector3 origin;	// !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 半直線
struct Ray {
	Vector3 origin;	// !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 線分
struct Segment {
	Vector3 origin;	// !< 始点
	Vector3 diff;   // !< 終点への差分ベクトル
};


// 平面
struct Plane {
	Vector3 normal;	// !< 法線
	float distance; // !< 距離
};


// 三角形
struct Triangle {
	Vector3 vertices[3]; // !< 頂点
};


// AABB
struct AABB {
	Vector3 min; // !< 最少点
	Vector3 max; // !< 最大点
};


// OBB
struct OBB {
	Vector3 center;			   // !< 中心点
	Vector3 orientations[3]{}; // !< 座標軸。正規化・直交必須
	Vector3 halfSize;          // !< 座標軸方向の長さの半分。中心から面までの距離
};