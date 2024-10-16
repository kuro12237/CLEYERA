#include "DirectionLIght.h"

using namespace Math::Matrix;

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;
using namespace Engine::Light;

DirectionalLight* DirectionalLight::GetInstance()
{
	static DirectionalLight instance;
	return &instance;
}

void DirectionalLight::Initialize()
{
	DirectionalLight::GetInstance()->buffer_ = make_unique<BufferResource<SDirectionLight>>();
	DirectionalLight::GetInstance()->buffer_->CreateResource();
	DirectionalLight::GetInstance()->light.intensity = 1.0f;
	DirectionalLight::GetInstance()->light.pos = { -1,1,0 };
	DirectionalLight::GetInstance()->light.useFlag = true;
	//DirectionalLight::GetInstance()->light.matrix = MatrixTransform::Identity();
	DirectionalLight::GetInstance()->worldMat_ = Math::Matrix::Identity();
	DirectionalLight::GetInstance()->viewMat_ = Math::Matrix::Identity();
}

void DirectionalLight::Update()
{
#ifdef _USE_IMGUI

	if (ImGui::TreeNode("directionLight"))
	{
		ImGui::DragFloat3("light", &DirectionalLight::GetInstance()->light.pos.x, -1.0f, 1.0f);
		ImGui::TreePop();
	}
#endif //_USE_IMGUI

	DirectionalLight::GetInstance()->buffer_->Map();
	//Translateの更新
	Matrix4x4 translateMatrix =
		Math::Matrix::TranslateMatrix(DirectionalLight::GetInstance()->light.pos);
	//worldTransformの更新
	DirectionalLight::GetInstance()->worldMat_ =
		Math::Matrix::Multiply(Math::Matrix::Identity(), translateMatrix);
	//view行列の更新
	DirectionalLight::GetInstance()->viewMat_ =
		Math::Matrix::Multiply(Math::Matrix::Inverse(translateMatrix),
			Math::Matrix::Inverse(Math::Matrix::Identity()));

	//DirectionalLight::GetInstance()->light.matrix = DirectionalLight::GetInstance()->viewMat_;
	DirectionalLight::GetInstance()->buffer_->Setbuffer(DirectionalLight::GetInstance()->light);
	DirectionalLight::GetInstance()->buffer_->UnMap();
}

void DirectionalLight::CommandCall(UINT n)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	commands.m_pList->SetGraphicsRootConstantBufferView(n, DirectionalLight::GetInstance()->buffer_->GetBuffer()->GetGPUVirtualAddress());
}
