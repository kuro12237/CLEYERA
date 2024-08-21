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

	void ImGuiUpdate();

	void Update();

	void Draw();

#pragma region Set

	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }

	void SetTransform(const TransformEular& transform) { worldTransform_.transform = transform; }

#pragma endregion

#pragma region Get

	uint32_t GetTexHandle() { return texHandle_; }
#pragma endregion


private:

	void CreateIndex();
	void CreateVertex();
	void CreateMaterial();

	unique_ptr<BufferResource<VertexData>>cVertex_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>cIndex = nullptr;
	unique_ptr<BufferResource<Material>>cMaterial_ = nullptr;
	Material material_ = {};

	uint32_t texHandle_ = 0;
	WorldTransform worldTransform_ = {};

	string defaultCubeMapName_ = "Resources/Default/CubeMap.dds";
	//Singleton
	SkyBox() = default;
	~SkyBox() = default;
	SkyBox(const 	SkyBox&) = delete;
	const 	SkyBox& operator=(const 	SkyBox&) = delete;
};
