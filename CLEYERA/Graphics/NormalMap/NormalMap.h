#pragma once
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"CreateResource.h"
#include"Pch.h"

#include<DirectXTex/DirectXTex.h>
#include <DirectXPackedVector.h>

struct CreateTex_param
{
	Vector2 pos;
	Vector4 color;
};
class NormalMap
{
public:

	static NormalMap* GetInstance();

	static  std::vector<vector<CreateTex_param>> CreateNormalMapTex(SModelData &normals,int32_t width,int32_t height);

	static uint32_t LoadNormalMap(vector<Vector3> normals);

private:

	//Singleton
	NormalMap() = default;
	~NormalMap() = default;
	NormalMap(const NormalMap&) = delete;
	const  NormalMap& operator=(const NormalMap&) = delete;
};