#include "ModelLineState.h"

//void ModelLineState::Initialize(Model* state)
//{
//
//	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData)*VertexSize);
//	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
//	resource_.Material = CreateResources::CreateBufferResource(sizeof(Vector4));
//
//	state;
//}
//
//void ModelLineState::CallPipelinexVertex(Model* state)
//{
//	state;
//}
//
//void ModelLineState::Draw(Model* state, const ViewProjection& viewprojection)
//{
//	VertexData* vertexData = nullptr;
//	Vector4* materialData = nullptr;
//
//	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
//	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
//
//
//	vertexData[0].position = {state->GetStartPos().x,state->GetStartPos().y,state->GetStartPos().z,state->GetStartPos().w };
//	vertexData[1].position = {state->GetEndPos().x,state->GetEndPos().y,state->GetEndPos().z,state->GetEndPos().w};
//
//	*materialData = state->GetColor();
//
//	CommandCall(worldTransform,viewprojection);
//}
//
//void ModelLineState::CommandCall(const WorldTransform& worldTransform, const ViewProjection& viewprojection)
//{
//	Commands commands = DirectXCommon::GetInstance()->GetCommands();
//	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Line;
//
//
//	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
//	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());
//
//	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
//	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);
//
//	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
//
//	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());
//	commands.m_pList->SetGraphicsRootConstantBufferView(1, worldTransform.buffer_->GetGPUVirtualAddress());
//	commands.m_pList->SetGraphicsRootConstantBufferView(2, viewprojection.buffer_->GetGPUVirtualAddress());
//
//	commands.m_pList->DrawInstanced(VertexSize, 1, 0, 0);
//}
