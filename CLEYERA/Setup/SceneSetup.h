#pragma once
#include"../CleyeraStruct.h"

#include"../Matrix/MatrixTransform.h"
#include"../Vector/VectorTransform.h"

struct  CameraTransform
{
	Transform transform;
	float aspectRatio;
};
class ScenceSetup
{
public:
	ScenceSetup();
	~ScenceSetup();
    
	/// <summary>
	/// シーンの初期化
	/// </summary>
	void SceneInitialize(CameraTransform camaraTransform_, int32_t kWindowWidth_, int32_t kwindowHeight_);



	void TransformUpdate(Transform cameraTransform_);


	Matrix4x4 worldViewProjectionMatrixFanc( Matrix4x4 MatrixTransform_);
    

private:

	MatrixTransform* matrixTransform = nullptr;
	VectorTransform* vectorTransform_ = nullptr;

	CameraTransform cameraTransform;
	Matrix4x4 cameraMatrix;
	Matrix4x4 projectionMatrix;
};

