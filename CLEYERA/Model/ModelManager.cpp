#include "ModelManager.h"

ModelManager* ModelManager::GetInstance()
{
	static ModelManager instance;
	return &instance;
}

void ModelManager::Initialize()
{

}

void ModelManager::Finalize()
{
	ModelManager::GetInstance()->objModelDatas_.clear();
}

void ModelManager::ModelLoadNormalMap()
{
	ModelManager::GetInstance()->isLoadNormalMap_ = true;
}

void ModelManager::ModelUseSubsurface()
{

	ModelManager::GetInstance()->isLoadNormalMap_ = true;
	ModelManager::GetInstance()->isUsesubsurface_ = true;
}

uint32_t ModelManager::LoadObjectFile(string directoryPath)
{
	if (ChackLoadObj(directoryPath))
	{
		//始めてだったら加算
		ModelManager::GetInstance()->objHandle_++;

		uint32_t modelHandle = ModelManager::GetInstance()->objHandle_;
		SModelData modelData = {};

		Assimp::Importer importer;
		string file("Resources/Models/" + directoryPath + "/" + directoryPath + ".obj");
		const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
		assert(scene->HasMeshes());

		//mesh解析
		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			aiMesh* mesh = scene->mMeshes[meshIndex];
			assert(mesh->HasNormals());
			assert(mesh->HasTextureCoords(0));
			//Fenceの解析
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
			{
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);
				//Vertex解析
				for (uint32_t element = 0; element < face.mNumIndices; ++element)
				{
					uint32_t vertexIndex = face.mIndices[element];
					aiVector3D& position = mesh->mVertices[vertexIndex];
					aiVector3D& normal = mesh->mNormals[vertexIndex];
					aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
					VertexData vertex;
					vertex.position = { position.x,position.y,position.z,1.0f };
					vertex.normal = { normal.x,normal.y,normal.z };
					vertex.texcoord = { texcoord.x,texcoord.y };
					//座標反転
					vertex.position.x *= -1.0f;
					vertex.normal.x *= -1.0f;
					modelData.vertices.push_back(vertex);
					// インデックスの解析
	
				}

			}
		}
		//materialの解析
		for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; materialIndex++)
		{
			aiMaterial* material = scene->mMaterials[materialIndex];
			if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
			{
				aiString texFilePath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &texFilePath);
				modelData.material.textureFilePath = "Resources/Models/" + directoryPath + "/" + texFilePath.C_Str();

			}
		}

		TextureManager::UnUsedFilePath();
		uint32_t texHandle = TextureManager::LoadPngTexture(modelData.material.textureFilePath);
		modelData.material.handle = texHandle;

		if (ModelManager::GetInstance()->isLoadNormalMap_)
		{
			const string normalFilePath = "Resources/Models/" + directoryPath + "/normalMap.png";
			TextureManager::UnUsedFilePath();
			uint32_t normalHandle = TextureManager::LoadPngTexture(normalFilePath);
			modelData.normalTexHandle = normalHandle;
			ModelManager::GetInstance()->isLoadNormalMap_ = false;
		}
		if (ModelManager::GetInstance()->isUsesubsurface_)
		{
			const string baseFilePath = "Resources/Models/" + directoryPath + "/baseTex.png";
			TextureManager::UnUsedFilePath();
			uint32_t baseTexHandle = TextureManager::LoadPngTexture(baseFilePath);
			modelData.baseTexHandle = baseTexHandle;
			ModelManager::GetInstance()->isUsesubsurface_ = false;

		}

		unique_ptr<Model>model = make_unique <Model>();
		model->CreateObj(modelData);
		ModelManager::GetInstance()->objModelDatas_[directoryPath] = make_unique<ModelObjData>(modelData, modelHandle,move(model));

		return modelHandle;
	}
	ModelManager::GetInstance()->isLoadNormalMap_ = false;
	ModelManager::GetInstance()->isUsesubsurface_ = false;
	return ModelManager::GetInstance()->objModelDatas_[directoryPath]->GetIndex();
}

SModelData ModelManager::GetObjData(uint32_t index)
{
	SModelData data{};
	for (const auto& [key, s] : ModelManager::GetInstance()->objModelDatas_)
	{
		if (s.get()->GetIndex() == index)
		{
			data = s.get()->GetData();
			data.texFilePath = key;
			return data;
		}
	}

	return data;
}

Model* ModelManager::GetModel(uint32_t index)
{
	Model*data =nullptr;
	for (const auto& [key, s] : ModelManager::GetInstance()->objModelDatas_)
	{
		if (s.get()->GetIndex() == index)
		{
			data = s.get()->GetModel();
			return data;
		}
	}

	return nullptr;
}

bool ModelManager::ChackLoadObj(string filePath)
{
	if (ModelManager::GetInstance()->objModelDatas_.find(filePath) == ModelManager::GetInstance()->objModelDatas_.end())
	{
		return true;
	}
	return false;
}

