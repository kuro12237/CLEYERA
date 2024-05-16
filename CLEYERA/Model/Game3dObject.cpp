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

void Game3dObject::Draw(WorldTransform worldTransform, CameraData view)
{
	if (model_ == nullptr)
	{
		return;
	}

	MaterialBuffer_->Map();

	material_.shininess = game3dObjectDesc_->shongDesc.shininess;
	material_.color = color_;
	material_.uvTransform = Math::Matrix::AffineMatrix(uvScale_, uvRotate, uvTranslate);
	material_.specular_ = game3dObjectDesc_->shongDesc.specular_;
	material_.roughness_ = roughness_;
	material_.metalness_ = metalness_;
	material_.scatterCoefficient = game3dObjectDesc_->sssDesc.scatterCoefficient_;
	material_.scatterDistance = game3dObjectDesc_->sssDesc.scatterDistance_;
	material_.absorptionCoefficient = game3dObjectDesc_->sssDesc.scatterCoefficient_;
	material_.grayFactor = game3dObjectDesc_->colorDesc.grayFactor_;

	MaterialBuffer_->Setbuffer(material_);
	MaterialBuffer_->UnMap();

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	if (game3dObjectDesc_->useLight)
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
	view.buffer_->CommandCall(3);

	DescriptorManager::rootParamerterCommand(4, LightingManager::dsvHandle());
	commands.m_pList->SetGraphicsRootConstantBufferView(5, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(6, texHandle_);

	if (game3dObjectDesc_->useLight)
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
	model_->Draw(view, 1);
}

bool Game3dObject::CommpandPipeline(SPSOProperty& PSO)
{
	switch (ModelShaderSelect_)
	{
	case PHONG_MODEL:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Phong_SkinningModel;
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
