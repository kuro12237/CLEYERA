#pragma once
#include"CreateResource.h"
#include"Pch.h"
#include"math/Matrix/MatrixTransform.h"

struct  PhongModelDesc
{
	float shininess = 192.0f;
	float specular_ = 2.0f;
};
struct  SSSModelDesc
{
	// 散乱係数
	float scatterCoefficient_ = 0.5f;
	// 吸収係数 
	float absorptionCoefficient_ = 0.5f;
	//光の伝播距離
	float scatterDistance_ = 0.5f;
};

struct PBRModelDesc
{
#pragma region 物理ベース
	float metalness_ = 1.0f;
	float roughness_ = 1.0f;
#pragma endregion
};

struct ColorModelDesc
{
	Math::Vector:: Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	Math::Vector::Vector3 uvScale_ = { 1,1,1 };
	Math::Vector::Vector3 uvRotate = { 0,0,0 };
	Math::Vector::Vector3 uvTranslate = { 0,0,0 };
    
	float grayFactor_ = 0.0f;
};

struct EdgeDesc {

	float mask = 0.0f;
	Math::Vector::Vector2 minmax = {};
	Math::Vector::Vector4 edgeColor = { 1.0f,1.0f,1.0f,1.0f };
};

struct Game3dObjectDesc
{
	PhongModelDesc phongDesc;
	SSSModelDesc sssDesc;
	PBRModelDesc pbrDesc;
	ColorModelDesc colorDesc;
	EdgeDesc edgeDesc;

	bool useLight = false;

};