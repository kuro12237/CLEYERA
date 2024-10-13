#pragma once
#include"Graphics/TextureManager/TextureManager.h"
#include"CreateResource/BufferResources.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"WorldTransform.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Light/LightingManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

class SkyBox
{
public:

	static SkyBox* GetInstance();

	void Initialize();

	void ImGuiUpdate();

	void Update();

	void Draw();
	void Reset() { worldTransform_.parent = nullptr; worldTransform_.transform = {}; }

#pragma region Set

	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }
	void SetTransform(const TransformEular& transform) { worldTransform_.transform = transform; }
	void SetParent(const WorldTransform& transform) { worldTransform_.parent = &transform; }
	
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

	bool initializeLock_ = false;
	uint32_t texHandle_ = 0;
	WorldTransform worldTransform_ = {};

	GlobalVariables* globalVariables_ = nullptr;


	string defaultCubeMapName_ = "Resources/Default/CubeMap.dds";
	string prevDefaultCubeMapName_ = "";


	//Singleton
	SkyBox() = default;
	~SkyBox() = default;
	SkyBox(const 	SkyBox&) = delete;
	const 	SkyBox& operator=(const 	SkyBox&) = delete;
};
