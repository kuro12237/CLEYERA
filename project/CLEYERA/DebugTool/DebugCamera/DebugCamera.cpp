#include"DebugCamera.h"

using namespace Math::Matrix;
using namespace Engine::DebugTools;
using namespace Engine::Buffer;

using namespace Engine::Camera;

void DebugCamera::Initialize() 
{
	cameraData_.Initialize();
	matRot_ = Math::Matrix::Identity();
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
			matRot_ = Math::Matrix::Identity();
		}
		ImGui::DragFloat3("offset", &offset_.x, -0.1f, 0.1f);
		ImGui::TreePop();
	}

#endif // _USE_IMGUI

}

void DebugCamera::Update()
{
	//中心地点からずらす
	Math::Vector::Vector3 offset = offset_;
	offset = Math::Vector::TransformNormal(offset,matRot_);
	worldTransform_.transform.translate = offset;

	RotateMove();
	//Translateの更新
	Matrix4x4 translateMatrix =
		Math::Matrix::TranslateMatrix(worldTransform_.transform.translate);
	//worldTransformの更新
	worldTransform_.matWorld =
		Math::Matrix::Multiply(matRot_, translateMatrix);
	//view行列の更新
	cameraData_.matView_ =
		Math::Matrix::Multiply(Math::Matrix::Inverse(translateMatrix),
			Math::Matrix::Inverse(matRot_));

	//cameraData_.UpdateMatrix();
	cameraData_.TransfarMatrix();
}

void DebugCamera::RotateMove()
{
	Matrix4x4 matRotate = Math::Matrix::Identity();
	//←の回転
	if (Input::GetInstance()->PushKey(DIK_LEFT))
	{
		matRotate = Math::Matrix::Multiply(matRotate, Math::Matrix::RotateYMatrix(rotateSpeed_.y));
	}//→の回転
	else if (Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		matRotate = Math::Matrix::Multiply(matRotate, Math::Matrix::RotateYMatrix(-rotateSpeed_.y));
	}
	//↑の回転
	if (Input::GetInstance()->PushKey(DIK_UP))
	{
		matRotate = Math::Matrix::Multiply(matRotate, Math::Matrix::RotateXMatrix(rotateSpeed_.x));
	}//↓の回転
	else if (Input::GetInstance()->PushKey(DIK_DOWN))
	{
		matRotate = Math::Matrix::Multiply(matRotate, Math::Matrix::RotateXMatrix(-rotateSpeed_.x));
	}
	matRot_ = Math::Matrix::Multiply(matRotate, matRot_);

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
