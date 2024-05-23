#pragma once
#include"Graphics/TextureManager/TextureManager.h"
#include"CreateResource/BufferResources.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"WorldTransform.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Light/LightingManager.h"

class SkyBox
{
public:

	static SkyBox* GetInstance();

	void Initialize();

	void Update();

	void Draw();

	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }

private:

	unique_ptr<BufferResource<VertexData>>cVertex_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>cIndex = nullptr;
	unique_ptr<BufferResource<Material>>cMaterial_ = nullptr;
	Material material_ = {};

	uint32_t texHandle_ = 0;
	WorldTransform worldTransform_ = {};
	//Singleton
	SkyBox() = default;
	~SkyBox() = default;
	SkyBox(const 	SkyBox&) = delete;
	const 	SkyBox& operator=(const 	SkyBox&) = delete;
};
