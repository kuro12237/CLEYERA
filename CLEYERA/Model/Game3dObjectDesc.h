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

struct ColorModelDesc
{
	float grayFactor_ = 0.0f;
};

enum ModelShaderSelect
{
	PHONG_MODEL = 0,
	UE4_BRDF = 1,
	PHONG_NORMAL_MODEL = 2,
	PHONG_SUBSURFACE_MODEL = 3
};

struct Game3dObjectDesc
{

	ModelShaderSelect select = PHONG_MODEL;
	PhongModelDesc shongDesc;
	SSSModelDesc sssDesc;
	ColorModelDesc colorDesc;
	bool useLight = false;

};