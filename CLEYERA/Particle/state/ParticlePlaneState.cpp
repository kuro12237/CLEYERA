#include"ParticlePlaneState.h"

using namespace Math::Matrix;

void ParticlePlaneState::Initialize(Particle* state)
{
	if (NumInstansing)
	{
		//NumInstansingInitialize�����Ăяo���ꂽ��Error��o��
		LogManager::Log("Particle Instansing Error");
		assert(0);
	}
	NumInstansing = state->GetNumInstancing();
	NumInstansingLock = true;

	resource_.instancingResource = CreateResources::CreateBufferResource(sizeof(ParticleData) * NumInstansing);
	dsvIndex = DescriptorManager::CreateInstancingSRV(NumInstansing, resource_.instancingResource, sizeof(ParticleData));

	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize);
	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
	resource_.Material = CreateResources::CreateBufferResource(sizeof(Material));
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, resource_.Index.Get());
	//resource_.Light = CreateResources::CreateBufferResource(sizeof(LightData));
	
}

void ParticlePlaneState::Draw(Particle* state,list<Particle_param>param, CameraData  viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;
	ParticleData* instansingData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	resource_.instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instansingData));

	vertexData[0].position = { pos.x - size,pos.y + size,pos.z ,pos.w };
	vertexData[0].texcoord = { 0.0f,0.0f };//00
	vertexData[0].normal = { 0.0f,1.0f,0.0f };

	vertexData[1].position = { pos.x + size,pos.y + size,pos.z ,pos.w };
	vertexData[1].texcoord = { 1.0f,0.0f };//10
	vertexData[1].normal = { 0.0f,1.0f,0.0f };

	vertexData[2].position = { pos.x - size,pos.y - size,pos.z,pos.w };
	vertexData[2].texcoord = { 0.0f,1.0f };//01
	vertexData[2].normal = { 0.0f,1.0f,0.0f };

	vertexData[3].position = { pos.x + size,pos.y - size,pos.z,pos.w };
	vertexData[3].texcoord = { 1.0f,1.0f };//11
	vertexData[3].normal = { 0.0f,1.0f,0.0f };

	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	materialData->color = { 1,1,1,1 };
	materialData->color = testColor;
	Math::Vector::Vector3 sv, rv, tv;
	sv = { 1.0f,1.0f,1.0f };
	materialData->uvTransform = Math::Matrix::AffineMatrix(sv, rv,tv);
	
	//Billbord�̌v�Z
	CarmeraBillbord(viewprojection);
	
	NumDrawInstansing = 0;

	for (list<Particle_param>::iterator particleIterator = param.begin();
		particleIterator != param.end(); ++particleIterator){

		//�X�P�[����o��
		sMat = Math::Matrix::ScaleMatrix((*particleIterator).worldTransform_.transform.scale);
		//���s�ړ��ړ�
		tMat = Math::Matrix::TranslateMatrix((*particleIterator).worldTransform_.transform.translate);
		//Affine�ϊ�
		Matrix4x4 matWorld = Math::Matrix::Multiply(sMat, Math::Matrix::Multiply(billboardMatrix, tMat));
		//view�ϊ�
		matWorld = Math::Matrix::Multiply(matWorld, Math::Matrix::Multiply(viewprojection.matView_, viewprojection.matProj_));
		//uv��Affine
		(*particleIterator).uvTransform_.matWorld= Math::Matrix::AffineMatrix(
			(*particleIterator).uvTransform_.transform.scale,
			(*particleIterator).uvTransform_.transform.rotate,
			(*particleIterator).uvTransform_.transform.translate
		);

		//���
		instansingData[NumDrawInstansing].WVP = matWorld;
		instansingData[NumDrawInstansing].world = Math::Matrix::Identity();
		instansingData[NumDrawInstansing].color = (*particleIterator).color_;
		instansingData[NumDrawInstansing].uvTransform = (*particleIterator).uvTransform_.matWorld;
		NumDrawInstansing++;
	}

	//LightData* lightData = nullptr;
	//resource_.Light->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

	//lightData->color = { 1.0f,1.0f,1.0f,1.0f };
	//lightData->direction = { 0,-1,0 };
	//lightData->intensity = 1.0f;
	CommandCall(state->GetTexhandle(),state, viewprojection);
}


void ParticlePlaneState::CarmeraBillbord(CameraData  view)
{
	//��]
	Matrix4x4 backToFrontMatrix = Math::Matrix::Identity();
	Matrix4x4 rm = Math::Matrix::RotateXYZMatrix(view.rotation_.x, view.rotation_.y, view.rotation_.z);

	billboardMatrix = Math::Matrix::Multiply(backToFrontMatrix, rm);
	billboardMatrix.m[3][0] = 0.0f;
	billboardMatrix.m[3][1] = 0.0f;
	billboardMatrix.m[3][2] = 0.0f;
}

void ParticlePlaneState::CommandCall(uint32_t TexHandle,Particle *state, CameraData  view)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty pso = Get3dParticlePipeline(state);
	state;
	//pso = GraphicsPipelineManager::GetInstance()->GetPso().LightingParticle3d.none;
	commands.m_pList->SetGraphicsRootSignature(pso.rootSignature.Get());
	commands.m_pList->SetPipelineState(pso.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	//�`���ݒ�BPSO�ɐݒ肵�Ă����̂Ƃ͂܂��ʁB������̂�ݒ肷��ƍl���Ă����Ηǂ�
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�}�e���A��CBuffer�̏ꏊ��ݒ�
	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	DescriptorManager::rootParamerterCommand(1, dsvIndex);
	DescriptorManager::rootParamerterCommand(2, TexHandle);

	//commands.m_pList->SetGraphicsRootConstantBufferView(3, resource_.Light->GetGPUVirtualAddress());
	//commands.m_pList->SetGraphicsRootConstantBufferView(4, view.buffer_->GetGPUVirtualAddress());
	//DescriptorManager::rootParamerterCommand(5, LightingManager::dsvHandle());
	//commands.m_pList->SetGraphicsRootConstantBufferView(6, LightingManager::GetBuffer()->GetGPUVirtualAddress());





	
	commands.m_pList->DrawIndexedInstanced(IndexSize,NumDrawInstansing, 0, 0, 0);
}


SPSOProperty ParticlePlaneState::Get3dParticlePipeline(Particle* state)
{
	SPSOProperty PSO = {};

	switch (state->GetBlendMode())
	{
	case BlendNone:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Particle3d.none;
		break;
	case BlendAdd:
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Particle3d.Add;
		break;
	case BlendSubtruct:
		assert(0);
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Subtruct;
		break;
	case BlendMultiply:
		assert(0);
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Multiply;
		break;
	case BlendScreen:
		assert(0);
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite2d.Screen;
		break;

	default:
		break;
	}
	return PSO;
}