#include "Line.h"

void LineModel::Create()
{
	vertex_ = make_unique<BufferResource<VertexData>>();
	vertex_->CreateResource(2);
	vertex_->CreateVertexBufferView();

	material_ = make_unique<BufferResource<Material>>();
	material_->CreateResource();

}

void LineModel::Draw(Math::Matrix::Matrix4x4 startMat, Math::Matrix::Matrix4x4 endMat, const CameraData& camera)
{
	startMat, endMat, camera;
	material_->Map();
	Material m;
	m.color = { 1, 1, 1, 1 };
	material_->Setbuffer(m);

	vector<VertexData> v;
	v.resize(2);
	v[0] = {};
	v[1] = {};
	v[0].position = { 0,0,0,1 };
	v[1].position = { 0.5f,0.0f,0.0f,1.0f };

	Math::Matrix::Matrix4x4 sm, em,Vp;
	Vp = Math::Matrix::Multiply( camera.matView_, camera.matProjection_);
	sm = Math::Matrix::Multiply(startMat,Vp);
	em = Math::Matrix::Multiply(endMat, Vp);

	Math::Vector::Vector3 ResultVertex = Math::Vector::TransformNormal({ v[0].position.x, v[0].position.y ,v[0].position.z }, sm);
	v[0].position = { ResultVertex.x,ResultVertex.y,ResultVertex.z,1.0f };

	ResultVertex = { em.m[3][0] * v[1].position.x,em.m[3][1] * v[1].position.y ,em.m[3][2] * v[1].position.z };
	v[1].position = { ResultVertex.x,ResultVertex.y,ResultVertex.z,1.0f };

	vertex_->Map();
	vertex_->Setbuffer(v);
	vertex_->UnMap();
	//マテリアル
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Line;
	list->SetGraphicsRootSignature(PSO.rootSignature.Get());
	list->SetPipelineState(PSO.GraphicsPipelineState.Get());

	material_->CommandCall(0);

	list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	list->DrawInstanced(2, 1, 0, 0);


}
