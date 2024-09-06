#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"Matrix/MatrixTransform.h"
#include"CreateResource.h"
#include"BufferResources.h"

struct CameraData {

	~CameraData() {};

	shared_ptr<BufferResource<TransformationViewMatrix>>buffer_ = nullptr;
	shared_ptr<BufferResource<TransformationViewMatrix>>psBuffer_ = nullptr;

	/// <summary>
	/// GPUに送る用
	/// </summary>
	TransformationViewMatrix BufferMatrix_ = {};

	Math::Vector::Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	Math::Vector::Vector3 translation_ = { 0.0f,0.0f,-15.0f };
	Math::Matrix::Matrix4x4 matView_{};
	Math::Matrix::Matrix4x4 matProj_{};
	Math::Matrix::Matrix4x4 OrthographicMatrix_{};
	Math::Matrix::Matrix4x4 matVP_{};
	Math::Matrix::Matrix4x4 matVPInverse_{};
	Math::Matrix::Matrix4x4 matProjInverse_{};
	float fov_ = 0.45f;
	float aspectRatio_ = float(WinApp::GetkCilientWidth()) / float(WinApp::GetkCilientHeight());

	float nearClip_ = 0.1f;
	float farClip_ = 1000.0f;

	void Initialize(Math::Vector::Vector3 r={0.0f,0.0f,0.0f}, Math::Vector::Vector3 t={0.0f,0.0f,-5.0f});

	void UpdateMatrix();

	void CreateBuffer();

	Math::Matrix::Matrix4x4 GetViewMat() { return matView_; }
	Math::Matrix::Matrix4x4 GetProjMat() { return matProj_; }

	void Map();
	void UnMap();
	void TransfarMatrix();	
};