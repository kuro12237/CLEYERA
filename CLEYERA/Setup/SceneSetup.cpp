#include "SceneSetup.h"

ScenceSetup::ScenceSetup()
{
	matrixTransform = new MatrixTransform();
	vectorTransform_ = new VectorTransform();
}

void ScenceSetup::SceneInitialize(CameraTransform cameraTransform_, int32_t kWindowWidth_, int32_t kwindowHeight_)
{
	cameraTransform.transform = cameraTransform_.transform;
	cameraTransform.aspectRatio = kWindowWidth_ / kwindowHeight_;
	//cameraMatrix = matrixTransform->MakeAffineMatrix(cameraTransform.transform.scale, cameraTransform.transform.rotate, cameraTransform.transform.translate);
}

void ScenceSetup::TransformUpdate(Transform cameraTransform_)
{
	//cameraTransform.transform.rotate = vectorTransform_->Add(cameraTransform.transform.rotate, cameraTransform_.rotate);
	//cameraTransform.transform.scale = vectorTransform_->Add(cameraTransform.transform.scale, cameraTransform_.scale);
	//cameraTransform.transform.translate = vectorTransform_->Add(cameraTransform.transform.translate, cameraTransform_.translate);
	//cameraTransform.transform.translate.x += cameraTransform_.translate.x;


}

Matrix4x4 ScenceSetup::worldViewProjectionMatrixFanc(Matrix4x4 MatrixTransform_)
{
	
	    cameraMatrix = matrixTransform->MakeAffineMatrix(cameraTransform.transform.scale, cameraTransform.transform.rotate, cameraTransform.transform.translate);

		Matrix4x4 viewMatrix=matrixTransform->Inverse( cameraMatrix);
		
		Matrix4x4 projectionMatrix = matrixTransform->MakePerspectiveFovMatrix(0.45f, 1280/720, 0.1f, 100.0f);
	
		Matrix4x4 worldViewProjectionMatrix =
			matrixTransform->Multiply(MatrixTransform_, matrixTransform->Multiply(viewMatrix, projectionMatrix));
		
	return worldViewProjectionMatrix;
}


