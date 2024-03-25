#include "ModelObjState.h"

ModelObjState::~ModelObjState()
{
	
}

void ModelObjState::Initialize(Model* state)
{
	
	resource_.Vertex = CreateResources::CreateBufferResource(
		sizeof(VertexData) * state->GetModelData().vertices.size()
	);

	resource_.BufferView =
		CreateResources::VertexCreateBufferView(
			sizeof(VertexData) * state->GetModelData().vertices.size(),
			resource_.Vertex.Get(),
			int(state->GetModelData().vertices.size()
		));
}

void ModelObjState::CallPipelinexVertex(Model* state)
{
	state;
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ModelObjState::Draw(Model* state, const CameraData& viewprojection)
{
	VertexData* vertexData = nullptr;
	
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	memcpy(vertexData, state->GetModelData().vertices.data(), sizeof(VertexData) * state->GetModelData().vertices.size());
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	
	if (state->GetUseLight())
	{
		viewprojection.buffer_->CommandCall(3);

		DescriptorManager::rootParamerterCommand(4, LightingManager::dsvHandle());
		commands.m_pList->SetGraphicsRootConstantBufferView(5, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	}

	commands.m_pList->DrawInstanced(UINT(state->GetModelData().vertices.size()), 1, 0, 0);
}