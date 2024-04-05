#include "Game3dObject.h"

void Game3dObject::Create()
{
	MaterialBuffer_ = make_unique<BufferResource<Material>>();
	MaterialBuffer_->CreateResource();

	cMaterialBuffer_ = make_unique<BufferResource<DefferredMaterial>>();
	cMaterialBuffer_->CreateResource(1);
}

void Game3dObject::SetModel(uint32_t index)
{

	if (prevModelIndex_ != index)
	{
	    model_ = ModelManager::GetModel(index);
		texHandle_ = ModelManager::GetObjData(index).material.handle;

		if (ModelManager::GetObjData(index).normalTexHandle==0)
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

void Game3dObject::Draw(WorldTransform worldTransform ,CameraData view)
{
	if (model_ == nullptr)
	{
		return;
	}

	model_->UseLight(UseLight_);

	MaterialBuffer_->Map();

	material_.shininess = shininess;
	material_.color = color_;
	material_.uvTransform = MatrixTransform::AffineMatrix(uvScale_, uvRotate, uvTranslate);
	material_.specular_    = specular_;
	material_.roughness_ = roughness_;
	material_.metalness_  = metalness_;
	material_.scatterCoefficient = scatterCoefficient_;
	material_.scatterDistance = scatterDistance_;
	material_.absorptionCoefficient = absorptionCoefficient_;

	MaterialBuffer_->Setbuffer(material_);
	MaterialBuffer_->UnMap();

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	if (UseLight_)
	{
		if (CommpandPipeline(PSO))
		{
			assert(0);
		}
	}
	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	model_->CommandCallPipelineVertex();

	Commands command = DirectXCommon::GetInstance()->GetCommands();

	MaterialBuffer_->CommandCall(0);
	worldTransform.buffer_->CommandCall(1);
	view.buffer_->CommandCall(2);
	DescriptorManager::rootParamerterCommand(4, LightingManager::dsvHandle());
	commands.m_pList->SetGraphicsRootConstantBufferView(5, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(6, texHandle_);

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
	model_->Draw(view);
}

void Game3dObject::ShadowDraw(const WorldTransform& worldTransform, const CameraData view)
{

	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().shadow;

	Commands command = DirectXCommon::GetInstance()->GetCommands();
	model_->CommandCallPipelineVertex();

	MaterialBuffer_->Map();
	material_.shininess = shininess;
	material_.color = color_;
	material_.uvTransform = MatrixTransform::AffineMatrix(uvScale_, uvRotate, uvTranslate);
	material_.specular_ = specular_;
	material_.roughness_ = roughness_;
	material_.metalness_ = metalness_;
	material_.scatterCoefficient = scatterCoefficient_;
	material_.scatterDistance = scatterDistance_;
	material_.absorptionCoefficient = absorptionCoefficient_;
	MaterialBuffer_->Setbuffer(material_);
	MaterialBuffer_->UnMap();


	command.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	command.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());
	model_->CommandCallPipelineVertex();

	MaterialBuffer_->CommandCall(0);
	worldTransform.buffer_->CommandCall(1);

	view.buffer_->CommandCall(2);
	DescriptorManager::rootParamerterCommand(4, LightingManager::dsvHandle());
	command.m_pList->SetGraphicsRootConstantBufferView(5, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(6, texHandle_);
	DirectionalLight::CommandCall(7);

	model_->Draw(view);
}

void Game3dObject::ColorDraw(const WorldTransform& worldTransform, const CameraData& view)
{
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().ColorModel3d;
	GraphicsPipelineManager::GetInstance()->GetPso().ColorModel3d;

	Commands command = DirectXCommon::GetInstance()->GetCommands();
	command.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	command.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	model_->CommandCallPipelineVertex();

	cMaterialBuffer_->Map();
	cMaterial_.color = { 1,1,1,1 };
	cMaterialBuffer_->Setbuffer(cMaterial_);
	cMaterialBuffer_->UnMap();

	cMaterialBuffer_->CommandCall(0);
	worldTransform.buffer_->CommandCall(1);
	view.buffer_->CommandCall(2);
	view.buffer_->CommandCall(3);

	DescriptorManager::rootParamerterCommand(4,texHandle_);
	model_->Draw(view);
}

void Game3dObject::NormalDraw(const WorldTransform& worldTransform, const CameraData& view)
{
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().NormalModel3d;
	Commands command = DirectXCommon::GetInstance()->GetCommands();
	command.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	command.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	model_->CommandCallPipelineVertex();

	cMaterialBuffer_->Map();
	cMaterial_.color = { 1,1,1,1 };
	cMaterialBuffer_->Setbuffer(cMaterial_);
	cMaterialBuffer_->UnMap();

	cMaterialBuffer_->CommandCall(0);
	worldTransform.buffer_->CommandCall(1);
	view.buffer_->CommandCall(2);
	view.buffer_->CommandCall(3);

	DescriptorManager::rootParamerterCommand(4, normalTexHandle_);
	model_->Draw(view);
}

void Game3dObject::PosDraw(const WorldTransform& worldTransform, const CameraData& view)
{
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().PosModel3d;
	Commands command = DirectXCommon::GetInstance()->GetCommands();
	command.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	command.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	model_->CommandCallPipelineVertex();

	cMaterialBuffer_->Map();
	cMaterial_.color = { 1,1,1,1 };
	cMaterialBuffer_->Setbuffer(cMaterial_);
	cMaterialBuffer_->UnMap();

	cMaterialBuffer_->CommandCall(0);
	worldTransform.buffer_->CommandCall(1);
	view.buffer_->CommandCall(2);
	view.buffer_->CommandCall(3);

	DescriptorManager::rootParamerterCommand(4, normalTexHandle_);
	model_->Draw(view);
}

bool Game3dObject::CommpandPipeline(SPSOProperty &PSO)
{
	switch (ModelShaderSelect_)
	{
	case PHONG_MODEL:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Phong_Model;
		break;

	case UE4_BRDF:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().PBR_Model;
		break;
	case PHONG_NORMAL_MODEL:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().PhongNormal_Model;
		break;
	case PHONG_SUBSURFACE_MODEL:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().PhongSubsurface_Model;
		break;

	default:
		break;
	}
	return false;
}
