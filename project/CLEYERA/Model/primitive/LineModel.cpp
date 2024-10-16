#include "LineModel.h"

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Primitive;
using namespace Engine::Buffer;
using namespace Engine::Manager;

void LineModel::Create(string name, uint32_t vertexNum)
{
	vertex_ = make_unique<BufferResource<VertexData>>();
	vertex_->CreateResource(2);
	vertex_->CreateVertexBufferView();

	material_ = make_unique<BufferResource<Material>>();
	material_->CreateResource();

	worldMat_ = make_unique<BufferResource<Math::Matrix::Matrix4x4>>();
	worldMat_->CreateResource();
	mat_ = Math::Matrix::Identity();

	verticesBuf_ = make_unique < BufferResource < Math::Vector::Vector3 >>();
	verticesBuf_->CreateResource(vertexNum);
	verticesBuf_->CreateInstancingResource(vertexNum, name, sizeof(Math::Vector::Vector3));
}

void LineModel::Draw()
{
	material_->Map();
	material_->Setbuffer(color_);
	material_->UnMap();

	vector<VertexData> v;
	v.resize(2);
	v[0].position = { 0.0f,0.0f,0.0f,1.0f };
	v[1].position = { 0.0f,0.0f,0.0f,1.0f };

	vertex_->Map();
	vertex_->Setbuffer(v);
	vertex_->UnMap();

	worldMat_->Map();
	worldMat_->Setbuffer(mat_);
	worldMat_->UnMap();

	verticesBuf_->Map();
	verticesBuf_->Setbuffer(lines_);
	verticesBuf_->UnMap();

	CommandCall();
}

void LineModel::CommandCall()
{
	ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::LINE_3d, "None");
	commandList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commandList->SetPipelineState(PSO.GraphicsPipelineState.Get());
	vertex_->CommandVertexBufferViewCall();
	material_->CommandCall(0);

	CameraManager::GetInstance()->VsCommandCall(1);
	worldMat_->CommandCall(2);
	DescriptorManager::GetInstance()->rootParamerterCommand(3, verticesBuf_->GetSrvIndex());
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	commandList->DrawInstanced(2, UINT(lines_.size()-1), 0, 0);
}
