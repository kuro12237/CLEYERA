#include "Game3dObject.h"

void Game3dObject::Create(unique_ptr<IPipelineCommand> piplineSelect)
{
	piplineHandler_ = make_unique<PipelineHandler>();
	if (!piplineSelect)
	{
		unique_ptr<IPipelineCommand>pipline = make_unique<Default3dPipline>();
		piplineHandler_->UsePipeline(pipline);
	}
	else
	{
		piplineHandler_->UsePipeline(piplineSelect);
	}

	MaterialBuffer_ = make_unique<BufferResource<Material>>();
	MaterialBuffer_->CreateResource();
}

void Game3dObject::SetModel(uint32_t index)
{
	if (prevModelIndex_ != index)
	{
		if (!game3dObjectDesc_)
		{
			LogManager::Log("None SetGame3dObjectDesc");
			assert(0);
		}
		model_ = ModelManager::GetModel(index);
		texHandle_ = ModelManager::GetObjData(index).material.handle;
		model_->SetDesc(*game3dObjectDesc_);
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

	material_.shininess = game3dObjectDesc_->phongDesc.shininess;
	material_.specular_ = game3dObjectDesc_->phongDesc.specular_;

	material_.color = game3dObjectDesc_->colorDesc.color_;
	Math::Matrix::Matrix4x4 colorMat =
		Math::Matrix::AffineMatrix(
			game3dObjectDesc_->colorDesc.uvScale_,
			game3dObjectDesc_->colorDesc.uvRotate,
			game3dObjectDesc_->colorDesc.uvTranslate
		);
	material_.uvTransform = colorMat;
	material_.grayFactor = game3dObjectDesc_->colorDesc.grayFactor_;

	material_.roughness_ = game3dObjectDesc_->pbrDesc.roughness_;
	material_.metalness_ = game3dObjectDesc_->pbrDesc.metalness_;
	material_.scatterCoefficient = game3dObjectDesc_->sssDesc.scatterCoefficient_;
	material_.scatterDistance = game3dObjectDesc_->sssDesc.scatterDistance_;
	material_.absorptionCoefficient = game3dObjectDesc_->sssDesc.scatterCoefficient_;

	MaterialBuffer_->Setbuffer(material_);
	MaterialBuffer_->UnMap();

	piplineHandler_->Call();

	Commands commands = DirectXCommon::GetInstance()->GetCommands();


	Commands command = DirectXCommon::GetInstance()->GetCommands();

	MaterialBuffer_->CommandCall(0);
	worldTransform.buffer_->CommandCall(1);
	view.buffer_->CommandCall(2);
	view.buffer_->CommandCall(3);

	DescriptorManager::rootParamerterCommand(4, LightingManager::dsvHandle());
	commands.m_pList->SetGraphicsRootConstantBufferView(5, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(6, texHandle_);

	//if (game3dObjectDesc_->useLight)
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
	if (model_->GetModelData().skinningFlag_&&model_->GetModelData().fileFormat=="GLTF")
	{
		DescriptorManager::rootParamerterCommand(7, palette_->GetSrvIndex());
	}
	model_->Draw(1);
}

void Game3dObject::CreateSkinningParameter()
{
	if (!model_)
	{
		assert(0);
	}
	if (name_ == "")
	{
		LogManager::Log("None SetName");
		assert(0);
	}
	//skeltonをコピー
	skeleton_ = model_->GetModelData().skeleton;
	inverseBindMatrices = model_->GetModelData().inverseBindMatrices;
	palette_ = make_unique<BufferResource<WellForGPU>>();
	palette_->CreateResource(uint32_t(skeleton_.joints.size()));
	palette_->CreateInstancingResource(uint32_t(skeleton_.joints.size()), name_, sizeof(WellForGPU));
	paletteParam_.resize(skeleton_.joints.size());
}

void Game3dObject::SkeletonUpdate(string fileName, float t)
{
	SAnimation::Animation animationData_ = AnimationManager::GetInstance()->GetData(fileName);
	AnimationManager::ApplyAnimation(skeleton_, animationData_, t);
	ModelManager::SkeletonUpdate(skeleton_);
}

void Game3dObject::SkinningUpdate()
{
	palette_->Map();
	for (size_t jointIndex = 0; jointIndex < skeleton_.joints.size(); ++jointIndex)
	{
		assert(jointIndex < inverseBindMatrices.size());

		paletteParam_[jointIndex].skeletonSpaceMatrix =
			Math::Matrix::Multiply(inverseBindMatrices[jointIndex], skeleton_.joints[jointIndex].skeletonSpaceMatrix);
		paletteParam_[jointIndex].skeletonSpaceInverseTransposeMatrix =
			Math::Matrix::TransposeMatrix(Math::Matrix::Inverse(paletteParam_[jointIndex].skeletonSpaceMatrix));
	}
	palette_->Setbuffer(paletteParam_);
}

bool Game3dObject::CommpandPipeline(SPSOProperty& PSO)
{
	switch (game3dObjectDesc_->select)
	{

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
