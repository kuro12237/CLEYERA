#pragma once
#include"Graphics/TextureManager/TextureManager.h"
#include"CreateResource/BufferResources.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"WorldTransform.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Light/LightingManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

/// <summary>
/// SkyBoxのクラス
/// </summary>
class SkyBox
{
public:

	static SkyBox* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// Imguiの更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// WorldTransformをリセット
	/// </summary>
	void Reset() { worldTransform_.parent = nullptr; worldTransform_.transform = {}; }

#pragma region Set

	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }
	void SetTransform(const Engine::Transform::TransformEular& transform) { worldTransform_.transform = transform; }
	void SetParent(const Engine::Transform::WorldTransform& transform) { worldTransform_.parent = &transform; }
	
#pragma endregion

#pragma region Get
	uint32_t GetTexHandle() { return texHandle_; }
#pragma endregion


private:

	void CreateIndex();
	void CreateVertex();
	void CreateMaterial();

	unique_ptr<Engine::Buffer::BufferResource<VertexData>>cVertex_ = nullptr;
	unique_ptr<Engine::Buffer::BufferResource<uint32_t>>cIndex = nullptr;
	unique_ptr<Engine::Buffer::BufferResource<Material>>cMaterial_ = nullptr;
	Material material_ = {};

	bool initializeLock_ = false;
	uint32_t texHandle_ = 0;
	Engine::Transform::WorldTransform worldTransform_ = {};

	GlobalVariables* globalVariables_ = nullptr;


	string defaultCubeMapName_ = "Resources/Default/CubeMap.dds";
	string prevDefaultCubeMapName_ = "";


	//Singleton
	SkyBox() = default;
	~SkyBox() = default;
	SkyBox(const 	SkyBox&) = delete;
	const 	SkyBox& operator=(const 	SkyBox&) = delete;
};
