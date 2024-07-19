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
		model_ = ModelManager::GetModel(index);
		model_->SetDesc(game3dObjectDesc_);
	}

	prevModelIndex_ = index;
}

void Game3dObject::Draw(WorldTransform worldTransform)
{
	if (model_ == nullptr)
	{
		return;
	}

	modelData_ = model_->GetModelData();

	if (skinningFlag_)
	{
		ComPtr<ID3D12GraphicsCommandList>command_list = DirectXCommon::GetInstance()->GetCommands().m_pList;
		command_list->SetComputeRootSignature(GraphicsPipelineManager::GetInstance()->GetPso().skinningCompute.rootSignature.Get());
		command_list->SetPipelineState(GraphicsPipelineManager::GetInstance()->GetPso().skinningCompute.GraphicsPipelineState.Get());

		DescriptorManager::rootParamerterCommand(0, palette_->GetSrvIndex());
		DescriptorManager::rootParamerterCommand(1, inputVertex_->GetSrvIndex());
		DescriptorManager::rootParamerterCommand(2, model_->GetInfluence()->GetSrvIndex());
		DescriptorManager::rootParamerterCommand(3, outputVertex_->GetSrvIndex());
		//頂点数
		command_list->SetComputeRootConstantBufferView(4, model_->GetVertexNum()->GetBuffer()->GetGPUVirtualAddress());

		command_list->Dispatch(UINT(modelData_.vertices.size() + 1023) / 1024, 1, 1);
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
	CameraManager::GetInstance()->CommandCall(2);
	CameraManager::GetInstance()->CommandCall(3);
	//4.5を使用
	LightingManager::GetInstance()->CallCommand();
	//テクスチャ
	DescriptorManager::rootParamerterCommand(6, modelData_.material.handle);
	//subsurface
	//DescriptorManager::rootParamerterCommand(8, baseTexHandle_);

	//ここを後でどうにかする
	if (skinningFlag_)
	{
		outputVertex_->CommandVertexBufferViewCall();
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
	modelData_ = model_->GetModelData();
	//skeltonをコピー
	skeleton_ = model_->GetModelData().skeleton;
	inverseBindMatrices = model_->GetModelData().inverseBindMatrices;
#pragma region Pallete作成

	string paletteName = name_ + "Pallette";
	palette_ = make_unique<BufferResource<WellForGPU>>();
	palette_->CreateResource(uint32_t(skeleton_.joints.size()));
	palette_->CreateInstancingResource(uint32_t(skeleton_.joints.size()), paletteName);
	paletteParam_.resize(skeleton_.joints.size());

#pragma endregion

#pragma region inputVertex作成

	string inputVertexName = name_ + "inputVertex";
	inputVertex_ = make_unique<BufferResource<VertexData>>();
	inputVertex_->CreateResource(uint32_t(modelData_.vertices.size()));
	inputVertex_->CreateInstancingResource(uint32_t(modelData_.vertices.size()), inputVertexName);
	inputVertexParam_.resize(modelData_.vertices.size());
	
	for (int i = 0; i < int(modelData_.vertices.size()); i++)
	{
		inputVertexParam_[i] = modelData_.vertices[i];
	}
	inputVertex_->Map();
	inputVertex_->Setbuffer(inputVertexParam_);
#pragma endregion

#pragma region OutputVertex作成

	string outputVertexName = name_ + "outputVertex";
	outputVertex_ = make_unique<BufferResource<VertexData>>();
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;
	uavDesc.Buffer.NumElements = UINT(modelData_.vertices.size());
	uavDesc.Buffer.CounterOffsetInBytes = 0;
	uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
	uavDesc.Buffer.StructureByteStride = sizeof(VertexData);

	outputVertex_->CreateUAVResource(uavDesc, outputVertexName, UINT(modelData_.vertices.size()));
	outputVertex_->CreateVertexBufferView();
	outputVertexParam_.resize(modelData_.vertices.size());


#pragma endregion


	skinningFlag_ = true;
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

Material Game3dObject::MaterialConverter()
{
	Material result = material_;
	result.shininess = game3dObjectDesc_.phongDesc.shininess;
	result.specular_ = game3dObjectDesc_.phongDesc.specular_;

	result.color = game3dObjectDesc_.colorDesc.color_;
	Math::Matrix::Matrix4x4 colorMat =
		Math::Matrix::AffineMatrix(
			game3dObjectDesc_.colorDesc.uvScale_,
			game3dObjectDesc_.colorDesc.uvRotate,
			game3dObjectDesc_.colorDesc.uvTranslate
		);
	result.uvTransform = colorMat;
	result.grayFactor = game3dObjectDesc_.colorDesc.grayFactor_;

	result.roughness_ = game3dObjectDesc_.pbrDesc.roughness_;
	result.metalness_ = game3dObjectDesc_.pbrDesc.metalness_;
	result.scatterCoefficient = game3dObjectDesc_.sssDesc.scatterCoefficient_;
	result.scatterDistance = game3dObjectDesc_.sssDesc.scatterDistance_;
	result.absorptionCoefficient = game3dObjectDesc_.sssDesc.scatterCoefficient_;

	return result;
}
