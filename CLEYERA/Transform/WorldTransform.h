#pragma once
#include"Pch.h"
#include"Matrix/MatrixTransform.h"
#include"CreateResource.h"
#include"CameraData.h"
#include"WinApp.h"
#include"BufferResources.h"

enum Projection
{
	PerspectiveFov = 0,
    OrthographicMatrix = 1
};

struct WorldTransform
{
	~WorldTransform() {};

	Math::Vector::Vector3 scale = {1.0f,1.0f,1.0f};
	Math::Vector::Vector3 rotation = {0.0f,0.0f,0.0f};
	Math::Vector::Vector3 translate = {0.0f,0.0f,0.0f};
	Math::Qua::Quaternion quaternion = {};

	Math::Matrix::Matrix4x4 matWorld = {};
	const WorldTransform* parent = {};

	shared_ptr<BufferResource<TransformationMatrix>>buffer_=nullptr;

	/// <summary>
	/// GPUに送る用
	/// </summary>
	TransformationMatrix BufferMatrix_ = {};

	void Initialize();
	void SRTSetting(Math::Vector::Vector3 s = { 1,1,1 }, Math::Vector::Vector3 r = { 0,0,0 }, Math::Vector::Vector3 t = {0,0,0});
	void UpdateMatrix();
	void TransfarMatrix();

	void UpdateEularMatrix();

	//void UpdateQuaternionMatrix();

	//void UpdateEularQuaternionMatrix();

	void SetParent(const WorldTransform& w) { parent = &w; }
	void DeleateParent();

	Math::Vector::Vector3 GetWorldPosition();
private:
	void CreateBuffer();
	void Map();
	void UnMap();
};

