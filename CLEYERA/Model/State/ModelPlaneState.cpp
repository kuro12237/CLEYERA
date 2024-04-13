#include "ModelPlaneState.h"





void ModelPlaneState::Initialize(Model* state)
{
	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize);

	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, resource_.Index.Get());
	state;
}

void ModelPlaneState::CallPipelinexVertex(Model* state)
{
	state;
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	SPSOProperty PSO = {};

	PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	


	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);


	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void ModelPlaneState::Draw(Model* state, const CameraData& viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	//LightData* lightData = nullptr;
	uint32_t* indexData = nullptr;


	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	Math::Vector::Vector4 pos = state->GetCenterPos();
	float size = state->GetSize();

	vertexData[0].position = { pos.x - size,pos.y,pos.z + size,pos.w };
	vertexData[0].texcoord = { 0.0f,1.0f };
	vertexData[0].normal = { 0.0f,1.0f,0.0f };

	vertexData[1].position = { pos.x - size,pos.y,pos.z - size,pos.w };
	vertexData[1].texcoord = { 0.0f,0.0f };
	vertexData[1].normal = { 0.0f,1.0f,0.0f };


	vertexData[2].position = { pos.x + size,pos.y,pos.z + size,pos.w };
	vertexData[2].texcoord = { 1.0f,1.0f };
	vertexData[2].normal = { 0.0f,1.0f,0.0f };

	vertexData[3].position = { pos.x + size,pos.y,pos.z - size,pos.w };
	vertexData[3].texcoord = { 1.0f,0.0f };
	vertexData[3].normal = { 0.0f,1.0f,0.0f };


	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	materialData->color = state->GetColor();
	materialData->uvTransform = Math::Matrix::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());


	CommandCall(state->GetTexHandle(),viewprojection);

}

void ModelPlaneState::CommandCall(uint32_t texHandle,const CameraData& viewprojection)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	viewprojection.buffer_->CommandCall(2);

	if (!texHandle==0)
	{
		DescriptorManager::rootParamerterCommand(3, texHandle);
	}

	//�`��(DrawCall/�h���[�R�[��)�B
	commands.m_pList->DrawIndexedInstanced(IndexSize, 1, 0, 0, 0);


}
