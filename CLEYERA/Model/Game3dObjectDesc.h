#pragma once

struct  PhongModelDesc
{
	float shininess = 70.0f;
	float specular_ = 1.0f;
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

enum ModelShaderSelect
{
	UE4_BRDF = 0,
	PHONG_NORMAL_MODEL = 1,
	PHONG_SUBSURFACE_MODEL = 2
};

struct Game3dObjectDesc
{

	ModelShaderSelect select = PHONG_NORMAL_MODEL;
	PhongModelDesc phongDesc;
	SSSModelDesc sssDesc;
	PBRModelDesc pbrDesc;
	ColorModelDesc colorDesc;

	bool useLight = false;

};