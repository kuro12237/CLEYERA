#include "ModelManager.h"

using namespace Engine::Objects;
using namespace Engine::Manager;

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

void ModelManager::UnUseFilePath()
{
	ModelManager::GetInstance()->isUseFilePath_ = false;
}

uint32_t ModelManager::LoadObjectFile(string directoryPath)
{
	if (ChackLoadObj(directoryPath))
	{
		//始めてだったら加算
		ModelManager::GetInstance()->objHandle_++;

		uint32_t modelHandle = ModelManager::GetInstance()->objHandle_;
		SModelData modelData = {};
		modelData.fileFormat = "OBJ";

		Assimp::Importer importer;
		string file;

		if (ModelManager::GetInstance()->isUseFilePath_)
		{
			file = ("Resources/Models/" + directoryPath + "/" + directoryPath + ".obj");
		}
		else {

			file = directoryPath;
		}
		const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
		assert(scene->HasMeshes());

		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			aiMesh* mesh = scene->mMeshes[meshIndex];
			assert(mesh->HasNormals());
			assert(mesh->HasTextureCoords(0));
			//頂点作成
			CreateVerteces(modelData, mesh);
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
		else
		{
			TextureManager::UnUsedFilePath();
			uint32_t normalHandle = TextureManager::LoadPngTexture("Resources/Default/normalMap.png");
			modelData.normalTexHandle = normalHandle;
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
		model->SetStateType(modelData, OBJECT);
		ModelManager::GetInstance()->objModelDatas_[directoryPath] = make_unique<ModelObjData>(modelData, modelHandle, move(model));

		return modelHandle;
	}
	ModelManager::GetInstance()->isLoadNormalMap_ = false;
	ModelManager::GetInstance()->isUsesubsurface_ = false;
	ModelManager::GetInstance()->isUseFilePath_ = true;
	return ModelManager::GetInstance()->objModelDatas_[directoryPath]->GetIndex();
}

uint32_t ModelManager::LoadGltfFile(string directoryPath, bool skinningFlag)
{
	if (ChackLoadObj(directoryPath))
	{
		//始めてだったら加算
		ModelManager::GetInstance()->objHandle_++;

		uint32_t modelHandle = ModelManager::GetInstance()->objHandle_;
		SModelData modelData = {};
		modelData.fileFormat = "GLTF";
		modelData.skinningFlag_ = skinningFlag;

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
			//頂点作成
			CreateVerteces(modelData, mesh);
			//bone作成
			// ここからBoneのデータを取得
			CreateBorn(modelData, mesh);
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
		modelData.skeleton = CreateSkeleton(modelData.node);
		SkeletonUpdate(modelData.skeleton);

		//tex
		TextureManager::UnUsedFilePath();
		uint32_t texHandle = TextureManager::LoadPngTexture(modelData.material.textureFilePath);
		modelData.material.handle = texHandle;

		//normalMap
		TextureManager::UnUsedFilePath();
		uint32_t normalHandle = TextureManager::LoadPngTexture("Resources/Default/normalMap.png");
		modelData.normalTexHandle = normalHandle;

		unique_ptr<Model>model = make_unique <Model>();
		model->SetStateType(modelData, GLTF);
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

			return data;
		}
	}

	return data;
}

SModelData ModelManager::GetModelData(const string filePath)
{
	return ModelManager::GetInstance()->objModelDatas_[filePath]->GetData();
}

Model* ModelManager::GetModel(uint32_t index)
{
	Model* data = nullptr;
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

Model* ModelManager::GetModel(const string filePath)
{
	return ModelManager::GetInstance()->objModelDatas_[filePath]->GetModel();
}

void ModelManager::SkeletonUpdate(SAnimation::Skeleton& skeleton)
{
	for (SAnimation::Joint& joint : skeleton.joints)
	{
		Math::Matrix::Matrix4x4 tm = Math::Matrix::TranslateMatrix(joint.transform.translate);
		Math::Matrix::Matrix4x4 rm = Math::Qua::RotateMatrix(joint.transform.quaternion);
		Math::Matrix::Matrix4x4 sm = Math::Matrix::ScaleMatrix(joint.transform.scale);
		Math::Matrix::Matrix4x4 localMat = Math::Matrix::Multiply(sm, Math::Matrix::Multiply(rm, tm));
		joint.localMatrix = localMat;
		if (joint.parent)
		{
			joint.skeletonSpaceMatrix = Math::Matrix::Multiply(joint.localMatrix, skeleton.joints[*joint.parent].skeletonSpaceMatrix);
		}
		else {
			joint.skeletonSpaceMatrix = joint.localMatrix;
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

	//paramをGet
	aiVector3D scale, translate;
	aiQuaternion quaternion;

	node->mTransformation.Decompose(scale, quaternion, translate);
	result.transform.scale = { scale.x,scale.y,scale.z };
	result.transform.quaternion = { quaternion.x,-quaternion.y,-quaternion.z,quaternion.w };
	result.transform.translate = { -translate.x,translate.y,translate.z };
	Math::Matrix::Matrix4x4 sm, rm, tm;
	sm = Math::Matrix::ScaleMatrix(result.transform.scale);
	rm = Math::Qua::RotateMatrix(result.transform.quaternion);
	tm = Math::Matrix::TranslateMatrix(result.transform.translate);

	result.localMatrix = Math::Matrix::Multiply(sm, Math::Matrix::Multiply(rm, tm));

	result.name = node->mName.C_Str();
	result.children.resize(node->mNumChildren);

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
	joint.skeletonSpaceMatrix = Math::Matrix::Identity();
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

void ModelManager::CreateVerteces(SModelData& data, aiMesh* mesh)
{
	data.vertices.resize(mesh->mNumVertices);
	for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
		aiFace& face = mesh->mFaces[faceIndex];
		assert(face.mNumIndices == 3);//三角形のみ
		for (uint32_t element = 0; element < face.mNumIndices; ++element) {
			uint32_t vertexIndex = face.mIndices[element];
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
			data.vertices[vertexIndex].position = { -position.x,position.y,position.z,1.0f };
			data.vertices[vertexIndex].normal = { -normal.x,normal.y,normal.z };
			data.vertices[vertexIndex].texcoord = { texcoord.x,texcoord.y };
			//Indexの解析
			data.indecs.push_back(vertexIndex);
		}
	}
}

void ModelManager::CreateBorn(SModelData& data, aiMesh* mesh)
{
	for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
		aiBone* bone = mesh->mBones[boneIndex];
		std::string jointName = bone->mName.C_Str();
		JointWeightData& jointWeightData = data.skinClusterData[jointName];
		aiMatrix4x4 bindPoseMatirxAssimp = bone->mOffsetMatrix.Inverse();
		aiVector3D scale, translate;
		aiQuaternion rotate;
		bindPoseMatirxAssimp.Decompose(scale, rotate, translate);
		//1 左手系のBindPoseMatrixを作る
		//変換
		Math::Vector::Vector3 sv, tv;
		Math::Qua::Quaternion rq;
		sv = { scale.x,scale.y,scale.z };
		tv = { -translate.x,translate.y,translate.z };
		rq = { rotate.x,-rotate.y,-rotate.z,rotate.w };

		Math::Matrix::Matrix4x4 bindPoseMatrix = Math::Matrix::AffineMatrix(sv, rq, tv);
		jointWeightData.inverseBindPoseMatrix = Math::Matrix::Inverse(bindPoseMatrix);

		// Weight情報を取り出す
		for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; ++weightIndex) {
			jointWeightData.vertexWeights.push_back({ bone->mWeights[weightIndex].mWeight,bone->mWeights[weightIndex].mVertexId });
		}
	}
}

SkinCluster ModelManager::CreateSkinCluster(const SAnimation::Skeleton& skeleton, const SModelData& modelData)
{
	SkinCluster skinCluster{};

	//influence
	skinCluster.influenceResource = CreateResources::CreateBufferResource(sizeof(VertexInfluence) * modelData.vertices.size());
	VertexInfluence* mappedInfuence = nullptr;
	skinCluster.influenceResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedInfuence));
	std::memset(mappedInfuence, 0, sizeof(VertexInfluence) * modelData.vertices.size());
	skinCluster.mappedInfluence = { mappedInfuence,modelData.vertices.size() };

	skinCluster.influenceBufferView.BufferLocation = skinCluster.influenceResource->GetGPUVirtualAddress();
	skinCluster.influenceBufferView.SizeInBytes = UINT(sizeof(VertexInfluence) * modelData.vertices.size());
	skinCluster.influenceBufferView.StrideInBytes = sizeof(VertexInfluence);

	skinCluster.inverseBindMatrices.resize(skeleton.joints.size());
	std::generate(skinCluster.inverseBindMatrices.begin(), skinCluster.inverseBindMatrices.end(), Math::Matrix::Identity);
	for (const auto& jointWeight : modelData.skinClusterData) {
		auto it = skeleton.jointMap.find(jointWeight.first);
		if (it == skeleton.jointMap.end()) {
			continue;
		}
		// (*it).secondにはjointのindexが入っているので、該当のIndexのinverseBindPoseMatrixを代入
		skinCluster.inverseBindMatrices[(*it).second] = jointWeight.second.inverseBindPoseMatrix;
		for (const auto& vertexWeight : jointWeight.second.vertexWeights) {
			auto& currentInfluence = skinCluster.mappedInfluence[vertexWeight.vertexIndex];
			// 空いているところに入れる
			for (uint32_t index = 0; index < kNumMaxInfluence; ++index) {
				// weight == 0 が空いている状態 その場所に代入
				if (currentInfluence.weights[index] == 0.0f) {
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointIndicess[index] = (*it).second;
					break;
				}
			}
		}
	}
	return skinCluster;
}