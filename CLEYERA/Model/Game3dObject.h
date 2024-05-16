#pragma once
#include"ModelManager.h"
#include"Light/DirectionLIght.h"
#include"Game3dObjectDesc.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"


class Game3dObject
{
public:
	Game3dObject() {};
	~Game3dObject() { };

	void Create();

	void SetModel(uint32_t index);

	void Draw(WorldTransform worldTransform, CameraData view);

#pragma region Set

	void SetDesc(const Game3dObjectDesc& desc) { game3dObjectDesc_ = &desc; }

	void SetUvScale(Math::Vector::Vector3 s) { uvScale_ = s; }
	void SetUvRotate(Math::Vector::Vector3 r) { uvRotate = r; }
	void SetTranslate(Math::Vector::Vector3 t) { uvTranslate = t; }

	void SetTexHandle(uint32_t index) { texHandle_ = index; }
	void SetNormalTex(uint32_t tex) { normalTexHandle_ = tex; }
	void SetBaseTex(uint32_t tex) { baseTexHandle_ = tex; }

	void SetColor(Math::Vector::Vector4 color) { color_ = color; }

	void SetMetalness(float m) { this->metalness_ = m; }
	void SetRoughness(float r) { this->roughness_ = r; }

	void SetlectModelPipeline(ModelShaderSelect number) { ModelShaderSelect_ = number; }

#pragma endregion

private:

	Model* model_ = nullptr;
	uint32_t prevModelIndex_ = 0;

	bool isIndexDraw = false;
	bool CommpandPipeline(SPSOProperty& PSO);

	unique_ptr<BufferResource<Material>>MaterialBuffer_ = nullptr;
	Material material_ = {};

	//defferd
	unique_ptr<BufferResource<DefferredMaterial>>cMaterialBuffer_ = nullptr;
	DefferredMaterial cMaterial_ = {};


	Math::Vector::Vector4 color_ = { 1,1,1,1 };
	Math::Vector::Vector3 uvScale_ = { 1,1,1 };
	Math::Vector::Vector3 uvRotate = { 0,0,0 };
	Math::Vector::Vector3 uvTranslate = { 0,0,0 };

#pragma region 物理ベース
	float metalness_ = 1.0f;
	float roughness_ = 1.0f;
#pragma endregion

	const Game3dObjectDesc* game3dObjectDesc_ = nullptr;

	uint32_t texHandle_ = 0;
	uint32_t normalTexHandle_ = 0;
	uint32_t baseTexHandle_ = 0;

	uint32_t ModelShaderSelect_ = 0;
};