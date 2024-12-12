#include "Game3dObject.h"

using namespace Engine::Buffer;
using namespace Engine::Transform;
using namespace Engine::Manager;
using namespace Engine::Objects;

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
		model_ = ModelManager::GetModel(index);
		model_->SetDesc(*game3dObjectDesc_);
	}

	prevModelIndex_ = index;
	modelData_ = model_->GetModelData();
}

void Game3dObject::ChangePipline(unique_ptr<IPipelineCommand> piplineSelect)
{
	piplineHandler_->UsePipeline(piplineSelect);
}


void Game3dObject::Draw(WorldTransform worldTransform)
{
	if (model_ == nullptr)
	{
		return;
	}


	MaterialBuffer_->Map();
    //Descの情報をMaterialに変換
	material_ = MaterialConverter();
	MaterialBuffer_->Setbuffer(material_);
	MaterialBuffer_->UnMap();

	//パイプラインを積む
	piplineHandler_->Call(modelData_);
	//マテリアル
	MaterialBuffer_->CommandCall(0);
	//行列
	worldTransform.buffer_->CommandCall(1);
	//カメラ
	CameraManager::GetInstance()->PsCommandCall(2);
	CameraManager::GetInstance()->VsCommandCall(3);
	//4.5を使用
	LightingManager::GetInstance()->CallCommand();
	//テクスチャ
	DescriptorManager::rootParamerterCommand(6, modelData_.material.handle);

	//subsurface
	//DescriptorManager::rootParamerterCommand(8, baseTexHandle_);

	//ここを後でどうにかする
	if (skinningFlag_)
	{
		DescriptorManager::rootParamerterCommand(8, palette_->GetSrvIndex());
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
	skinningFlag_ = true;
}

void Game3dObject::SkeletonUpdate()
{
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

Material Game3dObject::MaterialConverter()
{
	Material result = material_;
	result.shininess = game3dObjectDesc_->phongDesc.shininess;
	result.specular_ = game3dObjectDesc_->phongDesc.specular_;

	result.color = game3dObjectDesc_->colorDesc.color_;
	Math::Matrix::Matrix4x4 colorMat =
		Math::Matrix::AffineMatrix(
			game3dObjectDesc_->colorDesc.uvScale_,
			game3dObjectDesc_->colorDesc.uvRotate,
			game3dObjectDesc_->colorDesc.uvTranslate
		);
	result.uvTransform = colorMat;
	result.grayFactor = game3dObjectDesc_->colorDesc.grayFactor_;

	result.roughness_ = game3dObjectDesc_->pbrDesc.roughness_;
	result.metalness_ = game3dObjectDesc_->pbrDesc.metalness_;
	result.scatterCoefficient = game3dObjectDesc_->sssDesc.scatterCoefficient_;
	result.scatterDistance = game3dObjectDesc_->sssDesc.scatterDistance_;
	result.absorptionCoefficient = game3dObjectDesc_->sssDesc.scatterCoefficient_;
	result.dissolveMask = game3dObjectDesc_->edgeDesc.mask;
	result.dissolveEdgeMinMax = game3dObjectDesc_->edgeDesc.minmax;
	result.dissolveEdgeColor = game3dObjectDesc_->edgeDesc.edgeColor;

	return result;
}
