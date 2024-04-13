#pragma once
#include"Pch.h"
#include"Graphics/TextureManager/TextureManager.h"

#include"ModelPlaneState.h"
#include"ModelLineState.h"
#include"ModelSphereState.h"
#include"ModelObjState.h"

#include"WorldTransform.h"
#include"CameraData.h"
#include"Light/Light.h"

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
	void CreateModel(unique_ptr<IModelState> state, Vector4 CenterPos = { 0,0,0,1 }, float size = { 0.5 }, Vector4 color = { 1,1,1,1 });

	/// <summary>
	/// DrawLine用の初期化
	/// </summary>
	/// <param name="StertPosition"></param>
	/// <param name="EndPosition"></param>
	/// 
	void CreateLine(unique_ptr<IModelState> state, Vector4 StertPosition, Vector4 EndPosition, Vector4 Color = { 1,1,1,1 });

	/// <summary>
	/// modelをセット(初期化の時にしか使わないように)
	/// </summary>
	/// <param name="ModelHandle"></param>
	void SetModel(uint32_t handle);

	void CreateObj(SModelData modeldata);

	void CommandCallPipelineVertex();

	void Draw( const CameraData&viewprojection);

	/// <summary>
	/// ライトを使うか？
	/// </summary>
	void UseLight(bool flag) { this->uselight_ = flag; };

	void SetIsIndexDraw(bool flag) { isIndexDrawFlag_ = flag; }

#pragma region Get

	bool GetIsIndexDraw() { return isIndexDrawFlag_; }

	Vector4 GetColor() { return color_; }
	uint32_t GetTexHandle() { return texHandle_; }
	uint32_t GetModelHandle() { return modelHandle_; }

	Vector3 GetuvScale() { return uvScale_; }
	Vector3 GetuvRotate() { return uvRotate_; }
	Vector3 GetuvTranslate() { return uvTranslate_; }

	/// <summary>
	/// GetLineStartPos
	/// </summary>
	Vector4 GetStartPos() { return StartPos_; }
	/// <summary>
	/// GetLineEndPos
	/// </summary>
	Vector4 GetEndPos() { return EndPos_; }

	/// <summary>
	/// GetModelCenterPos
	/// </summary>
	Vector4 GetCenterPos() { return CenterPos_; }
	/// <summary>
	/// GetModelSize
	/// </summary>
	float GetSize() { return size_; }


	bool GetUseLight(){return uselight_;}

	SModelData GetModelData() { return modelData_; }

	//Light GetLight() { return testLight_; }
#pragma endregion 

private:

	Vector4 CenterPos_ = { 0,0,0,1 };
	float size_=1.5f;

	Vector4 StartPos_ = {};
	Vector4 EndPos_ = {};

	Vector4 color_ = { 1,1,1,1 };

	uint32_t texHandle_ = 0;
	uint32_t modelHandle_ = 0;
	uint32_t prevModelHandle_ = 0;
	
	Vector3 uvScale_ = {1,1,1};
	Vector3 uvRotate_ = {0,0,0};
	Vector3 uvTranslate_ = {0,0,0};

	bool uselight_ = false;

	unique_ptr<IModelState> state_ = nullptr;
	SModelData modelData_;

	bool isIndexDrawFlag_ = false;
};

