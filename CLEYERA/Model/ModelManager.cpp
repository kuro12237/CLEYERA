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

		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			aiMesh* mesh = scene->mMeshes[meshIndex];
			assert(mesh->HasNormals());
			assert(mesh->HasTextureCoords(0));
			//メモリの確保
			//Fenceの解析
			for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex)
			{
				aiVector3D& position = mesh->mVertices[vertexIndex];
				aiVector3D& normal = mesh->mNormals[vertexIndex];
				aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
				VertexData vertex;
				vertex.position = { -position.x,position.y,position.z,1.0f };
				vertex.normal = { -normal.x,normal.y,normal.z };
				vertex.texcoord = { texcoord.x,texcoord.y };
				//座標反転
				//vertex.position.x *= -1.0f;
				//vertex.normal.x *= -1.0f;
				modelData.vertices.push_back(vertex);
			}

			//modelData.indecs.resize(mesh->mNumFaces);
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
			{
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);

				for (uint32_t element = 0; element < face.mNumIndices; ++element)
				{
					uint32_t vertexIndex = face.mIndices[element];
					//indexPush
					modelData.indecs.push_back(vertexIndex);
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

uint32_t ModelManager::LoadGltfFile(string directoryPath)
{
	if (ChackLoadObj(directoryPath))
	{
		//始めてだったら加算
		ModelManager::GetInstance()->objHandle_++;

		uint32_t modelHandle = ModelManager::GetInstance()->objHandle_;
		SModelData modelData = {};

		Assimp::Importer importer;
		string file("Resources/Models/" + directoryPath + "/" + directoryPath + ".gltf");
		const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
		assert(scene->HasMeshes());
		//mesh解析
		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			aiMesh* mesh = scene->mMeshes[meshIndex];
			assert(mesh->HasNormals());
			assert(mesh->HasTextureCoords(0));
			//メモリの確保
			//Fenceの解析
			for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex)
			{
				aiVector3D& position = mesh->mVertices[vertexIndex];
				aiVector3D& normal = mesh->mNormals[vertexIndex];
				aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
				VertexData vertex;
				vertex.position = { position.x,position.y,position.z,1.0f };
				vertex.normal = { -normal.x,normal.y,normal.z };
				vertex.texcoord = { texcoord.x,texcoord.y };
				//座標反転
				//vertex.position.x *= -1.0f;
				//vertex.normal.x *= -1.0f;
				modelData.vertices.push_back(vertex);
			}

			//modelData.indecs.resize(mesh->mNumFaces);
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
			{
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);
	
				for (uint32_t element = 0; element < face.mNumIndices; ++element)
				{
					uint32_t vertexIndex = face.mIndices[element];
					//indexPush
					modelData.indecs.push_back(vertexIndex);
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

		//Nodeを読む
		modelData.node = ReadNodeData(scene->mRootNode);
		SkeletonUpdate(modelData.node.skeleton);

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
		ModelManager::GetInstance()->objModelDatas_[directoryPath] = make_unique<ModelObjData>(modelData, modelHandle, move(model));
		
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

void ModelManager::SkeletonUpdate(SAnimation::Skeleton& skeleton)
{
	for (SAnimation::Joint j : skeleton.joints)
	{
		Matrix4x4 tm = MatrixTransform::TranslateMatrix(j.transform.translate);
		Matrix4x4 rm = QuaternionTransform::RotateMatrix(j.transform.quaternion);
		Matrix4x4 sm = MatrixTransform::ScaleMatrix(j.transform.scale);
		Matrix4x4 localMat = MatrixTransform::Multiply(sm, MatrixTransform::Multiply(rm, tm));
		j.localMatrix = localMat;
		if (j.parent)
		{
			j.skeletonSpaceMatrix = MatrixTransform::Multiply(j.localMatrix,skeleton.joints[*j.parent].skeletonSpaceMatrix);
		}
		else {
			j.skeletonSpaceMatrix = j.localMatrix;
		}
    }

}

bool ModelManager::ChackLoadObj(string filePath)
{
	if (ModelManager::GetInstance()->objModelDatas_.find(filePath) == ModelManager::GetInstance()->objModelDatas_.end())
	{
		return true;
	}
	return false;
}

NodeData ModelManager::ReadNodeData(aiNode* node)
{
	NodeData result;

	aiMatrix4x4 aiLocalMatrix = node->mTransformation;
	aiLocalMatrix.Transpose();

	//paramをGet
	aiVector3D scale, translate;
	aiQuaternion quaternion;

	node->mTransformation.Decompose(scale, quaternion, translate);
	result.transform.scale = { scale.x,scale.y,scale.z };
	result.transform.quaternion = { quaternion.x,-quaternion.y,-quaternion.z,quaternion.w };
	result.transform.translate = { translate.x,translate.y,translate.z };
	Matrix4x4 sm, rm, tm;
	sm = MatrixTransform::ScaleMatrix(result.transform.scale);
	rm = QuaternionTransform::RotateMatrix(result.transform.quaternion);
	tm = MatrixTransform::TranslateMatrix(result.transform.translate);
	
	result.localMatrix = MatrixTransform::Multiply(sm, MatrixTransform::Multiply(rm, tm));

	result.name = node->mName.C_Str();
	result.children.resize(node->mNumChildren);
	result.skeleton = CreateSkeleton(result);

	for (uint32_t childrenIndex = 0; childrenIndex < node->mNumChildren; ++childrenIndex)
	{
		result.children[childrenIndex] = ReadNodeData(node->mChildren[childrenIndex]);
		
	}

	return result;
}

SAnimation::Skeleton ModelManager::CreateSkeleton(const NodeData& rootNode)
{
	SAnimation::Skeleton skeleton;
	skeleton.root = CreateJoint(rootNode, {}, skeleton.joints);
	for (const SAnimation::Joint& joint : skeleton.joints)
	{
		skeleton.jointMap.emplace(joint.name, joint.index);
    }
	return skeleton;
}

int32_t ModelManager::CreateJoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<SAnimation::Joint>& joints)
{
	SAnimation::Joint joint;
	joint.name = node.name;
	joint.localMatrix = node.localMatrix;
	joint.transform = node.transform;
	joint.skeletonSpaceMatrix = MatrixTransform::Identity();
	joint.index = int32_t(joints.size());
	joint.parent = parent;
	joints.push_back(joint);

	for (const NodeData& child : node.children)
	{
		int32_t  childIndex = CreateJoint(child, joint.index, joints);
		joints[joint.index].childlen.push_back(childIndex);

	}
	return joint.index;
}

