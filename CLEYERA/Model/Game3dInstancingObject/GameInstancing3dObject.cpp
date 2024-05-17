#include "GameInstancing3dObject.h"

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
	for (shared_ptr<IGameInstancing3dObject>&p : params_) 
	{
		if (p)
		{
			if (!p->GetBreakFlag())
			{
				instancingData_[count].WVP = p->GetMatrix();
				instancingData_[count].world = p->GetMatrix();
				count++;
			}
			if (p->GetBreakFlag())
			{
				p.reset();
			}
		}
	}
	instancing_->Map();
	instancing_->Setbuffer(instancingData_,uint32_t(params_.size()));
	instancing_->UnMap();

	material_->Map();
	material_->Setbuffer(materialData_);
	material_->UnMap();
}

void GameInstancing3dObject::Draw(const CameraData& camera)
{

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
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
	camera.buffer_->CommandCall(2);
	camera.buffer_->CommandCall(3);
	DescriptorManager::rootParamerterCommand(4, LightingManager::dsvHandle());
	commands.m_pList->SetGraphicsRootConstantBufferView(5, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(6, texHandle_);

	DescriptorManager::rootParamerterCommand(7, normalTexHandle_);
	if (UseLight_)
	{
		if (ModelShaderSelect_ == PHONG_NORMAL_MODEL || ModelShaderSelect_ == UE4_BRDF || ModelShaderSelect_ == PHONG_SUBSURFACE_MODEL)
		{
			DescriptorManager::rootParamerterCommand(7, normalTexHandle_);

			if (ModelShaderSelect_ == PHONG_SUBSURFACE_MODEL)
			{
				DescriptorManager::rootParamerterCommand(8, baseTexHandle_);
			}
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

	prevModelIndex_ = index;
}

void GameInstancing3dObject::PushVector(shared_ptr<IGameInstancing3dObject> obj,uint32_t index)
{
	if (params_[index])
	{
		params_[index].reset();
	}

	params_[index] = obj;
}

bool GameInstancing3dObject::CommpandPipeline(SPSOProperty& PSO)
{
	switch (ModelShaderSelect_)
	{

	case UE4_BRDF:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().PBR_Model;
		break;
	case PHONG_NORMAL_MODEL:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().phongNormalInstancing_Model;
		break;
	case PHONG_SUBSURFACE_MODEL:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().PhongSubsurface_Model;
		break;

	default:
		break;
	}
	return false;
}
