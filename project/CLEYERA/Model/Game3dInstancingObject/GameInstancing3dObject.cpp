#include "GameInstancing3dObject.h"

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Buffer;
using namespace Engine::Manager;


void GameInstancing3dObject::Create(const uint32_t& kNum, const string& name)
{
	instancingNum_ = kNum;
	name_ = name;

	instancing_ = make_unique<BufferResource<TransformationMatrix>>();
	instancing_->CreateResource(sizeof(TransformationMatrix) * kNum);
	instancing_->CreateInstancingResource(kNum, name_, sizeof(TransformationMatrix));

	material_ = make_unique<BufferResource<Material>>();
	material_->CreateResource();

	params_.resize(kNum);
	instancingData_.resize(kNum);
	materialData_.color = { 1,1,1,1 };
}

void GameInstancing3dObject::Transfar()
{
	int count = 0;
	for (shared_ptr<IGameInstancing3dObject>& p : params_)
	{
		if (p)
		{

			materialData_.uvTransform = Math::Matrix::AffineMatrix(p->GetUvScale(), Math::Vector::Vector3(0, 0, 0), { 0,0,0 });
			instancingData_[count].WVP = p->GetMatrix();
			instancingData_[count].world = p->GetMatrix();
			count++;
		}
	}
	instancing_->Map();
	instancing_->Setbuffer(instancingData_, uint32_t(params_.size()));
	instancing_->UnMap();

	material_->Map();
	material_->Setbuffer(materialData_);
	material_->UnMap();
}

void GameInstancing3dObject::Draw()
{

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_3d, "None");
	//if (UseLight_)
	{
		if (CommpandPipeline(PSO))
		{
			assert(0);
		}
	}
	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	material_->CommandCall(0);
	DescriptorManager::rootParamerterCommand(1, instancing_->GetSrvIndex());
	CameraManager::GetInstance()->PsCommandCall(2);
	CameraManager::GetInstance()->VsCommandCall(3);

	LightingManager::GetInstance()->CallCommand();
	DescriptorManager::rootParamerterCommand(6, texHandle_);
	DescriptorManager::rootParamerterCommand(7, normalTexHandle_);
	if (UseLight_)
	{
		//if (ModelShaderSelect_ == PHONG_NORMAL_MODEL || ModelShaderSelect_ == UE4_BRDF || ModelShaderSelect_ == PHONG_SUBSURFACE_MODEL)
		{
			DescriptorManager::rootParamerterCommand(7, normalTexHandle_);
		}
	}
	model_->Draw(uint32_t(params_.size()));
}

void GameInstancing3dObject::SetModel(const uint32_t& index)
{
	if (prevModelIndex_ != index)
	{
		model_ = ModelManager::GetModel(index);
		texHandle_ = ModelManager::GetObjData(index).material.handle;

		if (ModelManager::GetObjData(index).normalTexHandle == 0)
		{
			TextureManager::UnUsedFilePath();
			normalTexHandle_ = TextureManager::LoadPngTexture("Resources/Default/normalMap.png");
		}
		else {
			normalTexHandle_ = ModelManager::GetObjData(index).normalTexHandle;
		}

		baseTexHandle_ = ModelManager::GetObjData(index).baseTexHandle;
	}
	modelHandle_ = index;
	prevModelIndex_ = modelHandle_;
}

void GameInstancing3dObject::PushVector(shared_ptr<IGameInstancing3dObject> obj, uint32_t index)
{
	if (params_[index])
	{
		params_[index].reset();
	}

	params_[index] = obj;
}

bool GameInstancing3dObject::CommpandPipeline(SPSOProperty& PSO)
{

	PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PHONG, "Instancing_None");
	return false;
}
