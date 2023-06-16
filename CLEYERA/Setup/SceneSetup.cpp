#include "SceneSetup.h"

ScenceSetup::ScenceSetup()
{
	matrixTransform = new MatrixTransform();
	vectorTransform_ = new VectorTransform();
}

ScenceSetup::~ScenceSetup()
{
	delete matrixTransform;
	delete vectorTransform_;
}

void ScenceSetup::SceneInitialize(CameraTransform cameraTransform_, int32_t kWindowWidth_, int32_t kwindowHeight_)
{
	cameraTransform.transform = cameraTransform_.transform;
	cameraTransform.aspectRatio = float(kWindowWidth_) / float(kwindowHeight_);

	//正射影行列	
	//projectionMatrix = matrixTransform->MakeOrthographicMatrix(-160.f, 160.f, 200.0f, 300.0f, 0.0f, 1000.0f);
	
	//投資変換行列
	projectionMatrix = matrixTransform->MakePerspectiveFovMatrix(0.45,cameraTransform.aspectRatio, 0.1f, 100.0f);
}

void ScenceSetup::TransformUpdate(Transform cameraTransform_)
{
	cameraTransform.transform.rotate = vectorTransform_->Add(cameraTransform.transform.rotate, cameraTransform_.rotate);
	cameraTransform.transform.scale = vectorTransform_->Add(cameraTransform.transform.scale, cameraTransform_.scale);
	cameraTransform.transform.translate = vectorTransform_->Add(cameraTransform.transform.translate, cameraTransform_.translate);
}

Matrix4x4 ScenceSetup::worldViewProjectionMatrixFanc(Matrix4x4 MatrixTransform_)
{
	
	    cameraMatrix = matrixTransform->MakeAffineMatrix(
			cameraTransform.transform.scale, 
			cameraTransform.transform.rotate,
			cameraTransform.transform.translate);

		Matrix4x4 viewMatrix=matrixTransform->Inverse( cameraMatrix);
		
		Matrix4x4 worldViewProjectionMatrix =
			matrixTransform->Multiply(MatrixTransform_, matrixTransform->Multiply(viewMatrix, projectionMatrix));
		
	return worldViewProjectionMatrix;
}


