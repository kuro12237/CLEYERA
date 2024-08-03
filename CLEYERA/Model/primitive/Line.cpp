#include "Line.h"

void LineModel::Create()
{
	vertex_ = make_unique<BufferResource<VertexData>>();
	vertex_->CreateResource(2);
	vertex_->CreateVertexBufferView();

	material_ = make_unique<BufferResource<Material>>();
	material_->CreateResource();

	worldMat_ = make_unique<BufferResource<Math::Matrix::Matrix4x4>>();
	worldMat_->CreateResource();
	mat_ = Math::Matrix::Identity();
}

void LineModel::Draw()
{
	material_->Map();

	material_->Setbuffer(color_);

	vector<VertexData> v;
	v.resize(2);
	v[0].position = { start.x,start.y,start.z,1.0f };
	v[1].position = { end.x,end.y,end.z,1.0f };

	vertex_->Map();
	vertex_->Setbuffer(v);
	vertex_->UnMap();

	worldMat_->Map();
	worldMat_->Setbuffer(mat_);

	//マテリアル
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Line;
	list->SetGraphicsRootSignature(PSO.rootSignature.Get());
	list->SetPipelineState(PSO.GraphicsPipelineState.Get());
	vertex_->CommandVertexBufferViewCall();
	material_->CommandCall(0);

	CameraManager::GetInstance()->CommandCall(1);
	worldMat_->CommandCall(2);
	list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	list->DrawInstanced(2, 1, 0, 0);


}
