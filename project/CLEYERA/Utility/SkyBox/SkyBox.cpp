#include "SkyBox.h"

SkyBox* SkyBox::GetInstance()
{
	static SkyBox instance;
	return &instance;
}

void SkyBox::Initialize()
{
	CreateVertex();
	CreateIndex();
	CreateMaterial();
	TextureManager::UnUsedFilePath();
	texHandle_ = TextureManager::LoadDDSTexture(defaultCubeMapName_);
}

void SkyBox::ImGuiUpdate()
{
	if (ImGui::TreeNode("SkyBox"))
	{
		ImGui::DragFloat3("scale", &worldTransform_.transform.scale.x,0.1f);
		ImGui::DragFloat3("rotate", &worldTransform_.transform.rotate.x, 0.1f);
		ImGui::DragFloat3("translate", &worldTransform_.transform.translate.x, 0.1f);
		ImGui::TreePop();
	}
}

void SkyBox::Update()
{
	cMaterial_->Map();
	cMaterial_->Setbuffer(material_);
	worldTransform_.UpdateMatrix();
}

void SkyBox::Draw()
{
	if (texHandle_==0)
	{
		return;
	}

	ComPtr<ID3D12GraphicsCommandList>command = DirectXCommon::GetInstance()->GetCommands().m_pList;

	SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SKYBOX,"None");
	command->SetGraphicsRootSignature(pso.rootSignature.Get());
	command->SetPipelineState(pso.GraphicsPipelineState.Get());

	cVertex_->CommandVertexBufferViewCall();
	cIndex->CommandIndexBufferViewCall();

	cMaterial_->CommandCall(0);
	worldTransform_.buffer_->CommandCall(1);
	CameraManager::GetInstance()->PsCommandCall(2);
	CameraManager::GetInstance()->VsCommandCall(3);
	LightingManager::GetInstance()->CallCommand();
	DescriptorManager::rootParamerterCommand(6, texHandle_);
	command->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	command->DrawIndexedInstanced(36, 1, 0, 0, 0);
}

void SkyBox::CreateIndex()
{

	cIndex = make_unique<BufferResource<uint32_t>>();
	cIndex->CreateResource(36);
	cIndex->CreateIndexBufferView();
	cIndex->Map();
	vector<uint32_t> indices = {
		// 右
		0, 1, 2, 2, 1,3,
		// 左
		4, 5, 6, 6, 5, 7,
		// 前
		8, 9, 10, 10, 9, 11,
		//後ろ
		 12, 13, 14, 14, 13, 15,
		 // 上
		 16, 17, 18, 18, 17, 19,
		 // 下
		 20, 21, 22, 22, 21, 23
	};
	cIndex->Setbuffer(indices);
	cIndex->UnMap();
}

void SkyBox::CreateVertex()
{
	cVertex_ = make_unique<BufferResource<VertexData>>();
	cVertex_->CreateResource(24);
	cVertex_->CreateVertexBufferView();

	cVertex_->Map();
	vector<VertexData>vertexData;
	vertexData.resize(24);
	//右
	vertexData[0].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData[1].position = { 1.0f,1.0f,-1.0f,1.0f };
	vertexData[2].position = { 1.0f,-1.0f,1.0f,1.0f };
	vertexData[3].position = { 1.0f,-1.0f,-1.0f,1.0f };

	//左
	vertexData[4].position = { -1.0f,1.0f,-1.0f,1.0f };
	vertexData[5].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData[6].position = { -1.0f,-1.0f,-1.0f,1.0f };
	vertexData[7].position = { -1.0f,-1.0f,1.0f,1.0f };
	//前
	vertexData[8].position = { -1.0f,1.0f,1.0f,1.0f };
	vertexData[9].position = { 1.0f,1.0f,1.0f,1.0f };
	vertexData[10].position = { -1.0f,-1.0f,1.0f,1.0f };
	vertexData[11].position = { 1.0f,-1.0f,1.0f,1.0f };
	// 後ろ
	vertexData[12].position = { 1.0f,  1.0f, -1.0f, 1.0f };
	vertexData[13].position = { -1.0f,  1.0f, -1.0f, 1.0f };
	vertexData[14].position = { 1.0f, -1.0f, -1.0f, 1.0f };
	vertexData[15].position = { -1.0f, -1.0f, -1.0f, 1.0f };

	// 上
	vertexData[16].position = { -1.0f,  1.0f,  1.0f, 1.0f };
	vertexData[17].position = { -1.0f,  1.0f, -1.0f, 1.0f };
	vertexData[18].position = { 1.0f,  1.0f,  1.0f, 1.0f };
	vertexData[19].position = { 1.0f,  1.0f, -1.0f, 1.0f };

	// 下
	vertexData[20].position = { -1.0f, -1.0f,  1.0f, 1.0f };
	vertexData[21].position = { 1.0f, -1.0f,  1.0f, 1.0f };
	vertexData[22].position = { -1.0f, -1.0f, -1.0f, 1.0f };
	vertexData[23].position = { 1.0f, -1.0f, -1.0f, 1.0f };
	cVertex_->Setbuffer(vertexData);
	cVertex_->UnMap();
}

void SkyBox::CreateMaterial()
{

	cMaterial_ = make_unique<BufferResource<Material>>();
	cMaterial_->CreateResource();

	worldTransform_.Initialize();
	worldTransform_.transform.scale = { 24.0f,24.0f,24.0f };
}
