#include "ModelSphereState.h"



void ModelSphereState::Initialize(Model* state)
{
	int v = VertexNum * VertexNum * 4;
	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * v);
	
	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * v, resource_.Vertex.Get(), v);
	if (state->GetUseLight())
	{
		resource_.Light = CreateResources::CreateBufferResource(sizeof(LightData));
	}

	uint32_t i = VertexNum * VertexNum * 6;
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * i);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * i, resource_.Index.Get());
}

void ModelSphereState::CallPipelinexVertex(Model* state)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = {};


	PSO = GraphicsPipelineManager::GetInstance()->GetPso().shape;

	//テクスチャがある場合
	if (!state->GetTexHandle() == 0) {
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	}
	if (state->GetUseLight())
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().PBR_Model;
	}
	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ModelSphereState::Draw(Model* state,const CameraData& viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

#pragma region 球の座標処理
	const float LON_EVERY = float(std::numbers::pi) * 2.0f / float(VertexNum);

	const float LAT_EVERY = float(std::numbers::pi) / float(VertexNum);
	{
		for (int latIndex = 0; latIndex < VertexNum; ++latIndex) {
			//θ
			float lat = -float(std::numbers::pi) / 2.0f + LAT_EVERY * latIndex;

			for (int lonIndex = 0; lonIndex < VertexNum; ++lonIndex) {

				uint32_t Vstart = (latIndex * VertexNum + lonIndex) * 4;
				uint32_t Istart = (latIndex * VertexNum + lonIndex) * 6;

				float u = float(lonIndex) / float(VertexNum);
				float v = 1.0f - float(latIndex) / float(VertexNum);

				float lon = lonIndex * LON_EVERY;
				float length = 1.0f / VertexNum;

				float size_ = state->GetSize();
				//
				vertexData[Vstart].position.x = size_ * (cos(lat) * cos(lon));
				vertexData[Vstart].position.y = size_ * (sin(lat));
				vertexData[Vstart].position.z = size_ * (cos(lat) * sin(lon));
				vertexData[Vstart].position.w = 1.0f;
				vertexData[Vstart].texcoord.x = u;
				vertexData[Vstart].texcoord.y = v + length;
				vertexData[Vstart].normal.x = vertexData[Vstart].position.x;
				vertexData[Vstart].normal.y = vertexData[Vstart].position.y;
				vertexData[Vstart].normal.z = vertexData[Vstart].position.z;

				//
				vertexData[Vstart + 1].position.x = size_ * (cos(lat + LAT_EVERY)) * cos(lon);
				vertexData[Vstart + 1].position.y = size_ * (sin(lat + LAT_EVERY));
				vertexData[Vstart + 1].position.z = size_ * (cos(lat + LAT_EVERY)) * sin(lon);
				vertexData[Vstart + 1].position.w = 1.0f;
				vertexData[Vstart + 1].texcoord.x = u;
				vertexData[Vstart + 1].texcoord.y = v;
				vertexData[Vstart + 1].normal.x = vertexData[Vstart + 1].position.x;
				vertexData[Vstart + 1].normal.y = vertexData[Vstart + 1].position.y;
				vertexData[Vstart + 1].normal.z = vertexData[Vstart + 1].position.z;

				//
				vertexData[Vstart + 2].position.x = size_ * (cos(lat) * cos(lon + LON_EVERY));
				vertexData[Vstart + 2].position.y = size_ * (sin(lat));
				vertexData[Vstart + 2].position.z = size_ * (cos(lat) * sin(lon + LON_EVERY));
				vertexData[Vstart + 2].position.w = 1.0f;
				vertexData[Vstart + 2].texcoord.x = u + length;
				vertexData[Vstart + 2].texcoord.y = v + length;
				vertexData[Vstart + 2].normal.x = vertexData[Vstart + 2].position.x;
				vertexData[Vstart + 2].normal.y = vertexData[Vstart + 2].position.y;
				vertexData[Vstart + 2].normal.z = vertexData[Vstart + 2].position.z;

				//
				vertexData[Vstart + 3].position.x = size_ * (cos(lat + LAT_EVERY) * cos(lon + LON_EVERY));
				vertexData[Vstart + 3].position.y = size_ * (sin(lat + LAT_EVERY));
				vertexData[Vstart + 3].position.z = size_ * (cos(lat + LAT_EVERY) * sin(lon + LON_EVERY));
				vertexData[Vstart + 3].position.w = 1.0f;
				vertexData[Vstart + 3].texcoord.x = u + length;
				vertexData[Vstart + 3].texcoord.y = v;
				vertexData[Vstart + 3].normal.x = vertexData[Vstart + 3].position.x;
				vertexData[Vstart + 3].normal.y = vertexData[Vstart + 3].position.y;
				vertexData[Vstart + 3].normal.z = vertexData[Vstart + 3].position.z;


				indexData[Istart] = Vstart;
				indexData[Istart + 1] = Vstart + 1;
				indexData[Istart + 2] = Vstart + 2;

				indexData[Istart + 3] = Vstart + 1;
				indexData[Istart + 4] = Vstart + 3;
				indexData[Istart + 5] = Vstart + 2;
			}
		}
	}
#pragma endregion

	ImGui::Begin("direction");
	ImGui::SliderFloat3("t", &testLightDirection.x, -1.0f, 1.0f);
	ImGui::SliderFloat("shininess", &shininess, 1.0f, 70.0f);
	ImGui::End();

	materialData->color = state->GetColor();
	materialData->shininess = shininess;
	materialData->uvTransform = MatrixTransform::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());
	if (state->GetUseLight())
	{
		LightData* lightData = nullptr;
		resource_.Light->Map(0, nullptr, reinterpret_cast<void**>(&lightData));
		

		lightData->color = { 1.0f,1.0f,1.0f,1.0f };
		lightData->direction = {0,1,0};
		lightData->intensity = 1.0f;
	
	}


	CommandCall(state,viewprojection);
}

void ModelSphereState::CommandCall(Model*state, const CameraData& viewprojection)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	if (!state->GetTexHandle() == 0)
	{
		DescriptorManager::rootParamerterCommand(3, state->GetTexHandle());
	}
	if (state->GetUseLight())
	{
		commands.m_pList->SetGraphicsRootConstantBufferView(4, resource_.Light->GetGPUVirtualAddress());
		viewprojection.buffer_->CommandCall(5);
		
		DescriptorManager::rootParamerterCommand(6, LightingManager::dsvHandle());
		commands.m_pList->SetGraphicsRootConstantBufferView(7, LightingManager::GetBuffer()->GetGPUVirtualAddress());
	}
	
	commands.m_pList->DrawIndexedInstanced(VertexNum * VertexNum * 6, 1, 0, 0, 0);
}
