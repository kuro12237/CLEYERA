#include"DebugCamera.h"

void DebugCamera::Initialize() 
{
	cameraData_.Initialize();
	matRot_ = MatrixTransform::Identity();
	worldTransform_.Initialize();
}

void DebugCamera::ImGuiUpdate()
{
#ifdef _USE_IMGUI

	if (ImGui::TreeNode("DebugCamera"))
	{
		ImGui::Checkbox("DebugCameraUse", &isUse_);
		if (ImGui::Button("Initialize"))
		{
			offset_ = DfOffset_;
			matRot_ = MatrixTransform::Identity();
		}
		ImGui::DragFloat3("offset", &offset_.x, -0.1f, 0.1f);
		ImGui::TreePop();
	}

#endif // _USE_IMGUI

}

void DebugCamera::Update()
{
	//中心地点からずらす
	Vector3 offset = offset_;
	offset = VectorTransform::TransformNormal(offset,matRot_);
	worldTransform_.translate = offset;

	RotateMove();
	//Translateの更新
	Matrix4x4 translateMatrix =
		MatrixTransform::TranslateMatrix(worldTransform_.translate);
	//worldTransformの更新
	worldTransform_.matWorld =
		MatrixTransform::Multiply(matRot_, translateMatrix);
	//view行列の更新
	cameraData_.matView_ =
		MatrixTransform::Multiply(MatrixTransform::Inverse(translateMatrix),
			MatrixTransform::Inverse(matRot_));

	//cameraData_.UpdateMatrix();
	cameraData_.TransfarMatrix();
}

void DebugCamera::RotateMove()
{
	Matrix4x4 matRotate = MatrixTransform::Identity();
	//←の回転
	if (Input::GetInstance()->PushKey(DIK_LEFT))
	{
		matRotate = MatrixTransform::Multiply(matRotate, MatrixTransform::RotateYMatrix(rotateSpeed_.y));
	}//→の回転
	else if (Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		matRotate = MatrixTransform::Multiply(matRotate, MatrixTransform::RotateYMatrix(-rotateSpeed_.y));
	}
	//↑の回転
	if (Input::GetInstance()->PushKey(DIK_UP))
	{
		matRotate = MatrixTransform::Multiply(matRotate, MatrixTransform::RotateXMatrix(rotateSpeed_.x));
	}//↓の回転
	else if (Input::GetInstance()->PushKey(DIK_DOWN))
	{
		matRotate = MatrixTransform::Multiply(matRotate, MatrixTransform::RotateXMatrix(-rotateSpeed_.x));
	}
	matRot_ = MatrixTransform::Multiply(matRotate, matRot_);

}

CameraData DebugCamera::GetData(const CameraData& camera)
{
	if (isUse_)
	{
		cameraData_.TransfarMatrix();
		return cameraData_;
	}
	return camera;
}
