#pragma once
#include"Pch.h"
#include"Graphics/TextureManager/TextureManager.h"

#include"ModelObjState.h"
#include"ModelSkinningState.h"

#include"WorldTransform.h"
#include"CameraData.h"
#include"Light/Light.h"
#include"Game3dObjectDesc.h"

class Model
{
public:
	~Model();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="state"></param>
	/// <param name="CenterPos"></param>
	/// <param name="size"></param>
	/// <param name="color"></param>
	void CreateModel(unique_ptr<IModelState> state, Math::Vector::Vector4 CenterPos = { 0,0,0,1 }, float size = { 0.5 }, Math::Vector::Vector4 color = { 1,1,1,1 });

	void CreateObj(SModelData modeldata, unique_ptr<IModelState>state);

	void CommandCallPipelineVertex();

	void Draw(uint32_t instancingNum);

	void SetDesc(const Game3dObjectDesc& desc) { desc_ = &desc; }

#pragma region Get

	Math::Vector::Vector4 GetColor() { return color_; }
	uint32_t GetTexHandle() { return texHandle_; }
	uint32_t GetModelHandle() { return modelHandle_; }

	Math::Vector::Vector3 GetuvScale() { return uvScale_; }
	Math::Vector::Vector3 GetuvRotate() { return uvRotate_; }
	Math::Vector::Vector3 GetuvTranslate() { return uvTranslate_; }

	/// <summary>
	/// GetModelCenterPos
	/// </summary>
	Math::Vector::Vector4 GetCenterPos() { return CenterPos_; }
	/// <summary>
	/// GetModelSize
	/// </summary>
	float GetSize() { return size_; }

	SModelData GetModelData() { return modelData_; }

	Game3dObjectDesc GetDesc() { return *desc_; }

#pragma endregion 

private:

	const Game3dObjectDesc* desc_ = nullptr;

	Math::Vector::Vector4 CenterPos_ = { 0,0,0,1 };
	float size_=1.5f;

	Math::Vector::Vector4 color_ = { 1,1,1,1 };

	uint32_t texHandle_ = 0;
	uint32_t modelHandle_ = 0;
	uint32_t prevModelHandle_ = 0;
	
	Math::Vector::Vector3 uvScale_ = {1,1,1};
	Math::Vector::Vector3 uvRotate_ = {0,0,0};
	Math::Vector::Vector3 uvTranslate_ = {0,0,0};

	unique_ptr<IModelState> state_ = nullptr;
	SModelData modelData_;

};

