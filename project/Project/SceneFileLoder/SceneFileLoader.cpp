#include "SceneFileLoader.h"

SceneFileLoader* SceneFileLoader::GetInstance()
{
	static SceneFileLoader instance;
	return &instance;
}

shared_ptr<LevelData> SceneFileLoader::ReLoad(const string& filePath)
{

	ifstream file = FileLoader::JsonLoadFile("Resources/levelData/" + filePath);
	file >> deserialized;
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//scene����Ȃ��������G���[��f��
	string name = deserialized["name"].get<string>();
	assert(name.compare("scene") == 0);

	if (!levelData)
	{
		levelData = make_unique<LevelData>();

	}

	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));

		std::string type = object["type"].get<string>();

		if (type.compare("MESH") == 0)
		{
			LoadMeshData(levelData, object);
		}

		if (type.compare("CAMERA") == 0)
		{
			LoadCameraData(levelData, object);
		}
	}
	return levelData;
}

AABB SceneFileLoader::LoadCollider(nlohmann::json& object)
{
	AABB aabb = {};
	string type = object["type"].get<string>();
	if (type == "Box")
	{
		aabb.max.x = float(object["size"][0]) / 2.0f;
		aabb.max.y = float(object["size"][2]) / 2.0f;
		aabb.max.z = float(object["size"][1]) / 2.0f;
		aabb.min.x = -float(object["size"][0]) / 2.0f;
		aabb.min.y = -float(object["size"][2]) / 2.0f;
		aabb.min.z = -float(object["size"][1]) / 2.0f;

	}
	return aabb;
}

void SceneFileLoader::LoadMeshData(shared_ptr<LevelData>& levelData, nlohmann::json& object)
{
	shared_ptr<Game3dObjectData> obj3dData = {};
	shared_ptr<Game3dInstancingObjectData> obj3dInstancingData = {};

	string drawType = object["DrawType"].get<string>();
	string objectName = object["name"].get<string>();
	uint32_t modelHandle = 0;

	//�ʏ�\��
	if (drawType.compare("Normal") == 0)
	{
		string name = object["name"].get<string>();
		{
			obj3dData = make_shared<Game3dObjectData>();

			obj3dData->SetObjName(objectName);
			obj3dData->SetObjectType("MESH");

			std::string modelFileName;
			Game3dObjectDesc objectDesc;
			vector<string>childName;

			objectDesc.useLight = true;

			//model�̃t�@�C���ǂݍ���
			if (object.contains("file_name"))
			{
				string fileType = object["ModelFileType"].get<string>();
				string fileName = object["file_name"].get<string>();
				if (fileType == "obj")
				{
					ModelManager::ModelLoadNormalMap();
					modelHandle = ModelManager::LoadObjectFile(fileName);
				}
				if (fileType == "gltf")
				{
					modelHandle = ModelManager::LoadGltfFile(fileName, true);
					obj3dData->SetModelFilePath(fileName);
					obj3dData->SetObjectType("ARMATURE");
				}
			}
			//transform��Get
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);

			if (object.contains("collider"))
			{
				AABB aabb = LoadCollider(object["collider"]);
				aabb.max = Math::Vector::Multiply(transformEular.scale, aabb.max);
				aabb.min = Math::Vector::Multiply(transformEular.scale, aabb.min);
				obj3dData->SetAABB(aabb);
			}

			if (object.contains("children"))
			{
				nlohmann::json& child = object["children"];

				for (size_t i = 0; i < child.size(); i++)
				{
					std::string type = child[i]["type"].get<string>();

					if (type.compare("MESH") == 0)
					{
						LoadObj3dData(levelData, obj3dData, child[i]);
					}
					if (type.compare("CAMERA") == 0)
					{
						LoadChildCameraData(levelData, obj3dData.get(), child[i]);
					}
				}
			}
			//�ۑ�
			obj3dData->Initialize(transformEular, objectDesc, modelHandle);

			levelData->obj3dData[objectName] = move(obj3dData);
		}
	}
	//�C���X�^���V���O�\��
	if (drawType.compare("Instancing") == 0)
	{
		string objectINstancingGrop = object["InstancingObjName"].get<string>();
		if (levelData->objInstancing3dData.find(objectINstancingGrop) != levelData->objInstancing3dData.end())
		{

			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();

			AABB aabb = LoadCollider(object["collider"]);
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			aabb.max = Math::Vector::Multiply(transformEular.scale, aabb.max);
			aabb.min = Math::Vector::Multiply(transformEular.scale, aabb.min);

			transforms->SetAABB(aabb);
			transforms->SetTransformEular(transformEular);
			transforms->Update();
			levelData->objInstancing3dData[objectINstancingGrop]->PushBackTransform(transforms);

			uint32_t size = uint32_t(levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms().size());

			levelData->objInstancing3dData[objectINstancingGrop]->PushObjectData(
				levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms()[size - 1], size);
		}
		else
		{
			//�C���X�^���X�̐���
			obj3dInstancingData = make_shared<Game3dInstancingObjectData>();

			//model�̃t�@�C���ǂݍ���
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"];
				ModelManager::ModelLoadNormalMap();
				modelHandle = ModelManager::LoadObjectFile(fileName);
			}
			else
			{
				ModelManager::ModelLoadNormalMap();
				modelHandle = ModelManager::LoadObjectFile("DfCube");
			}

			obj3dInstancingData->Initialize(objectINstancingGrop, modelHandle);

			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();

			//transform��Get
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			transforms->SetTransformEular(transformEular);

			AABB aabb = LoadCollider(object["collider"]);
			aabb.max = Math::Vector::Multiply(transformEular.scale, aabb.max);
			aabb.min = Math::Vector::Multiply(transformEular.scale, aabb.min);

			transforms->SetAABB(aabb);

			transforms->Update();

			obj3dInstancingData->PushBackTransform(transforms);
			//�ۑ�
			levelData->objInstancing3dData[objectINstancingGrop] = move(obj3dInstancingData);

			uint32_t size = uint32_t(levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms().size());
			levelData->objInstancing3dData[objectINstancingGrop]->PushObjectData(
				levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms()[size - 1], size);
		}
	}
}

void SceneFileLoader::LoadObj3dData(shared_ptr<LevelData>& levelData, shared_ptr<Game3dObjectData>& data, nlohmann::json object)
{
	shared_ptr<Game3dObjectData> obj3dData = {};
	shared_ptr<Game3dInstancingObjectData> obj3dInstancingData = {};

	string drawType = object["DrawType"].get<string>();
	string objectName = object["name"].get<string>();

	data->PushBackChildren(objectName);

	//�ʏ�\��
	if (drawType.compare("Normal") == 0)
	{
		obj3dData = make_shared<Game3dObjectData>();
		obj3dData->SetObjName(objectName);
		obj3dData->SetObjectType("MESH");

		std::string modelFileName;
		Game3dObjectDesc objectDesc;
		uint32_t modelHandle = 0;
		vector<string>childName;

		objectDesc.useLight = true;
		//model�̃t�@�C���ǂݍ���
		if (object.contains("file_name"))
		{
			string fileName = object["file_name"].get<string>();
			ModelManager::ModelLoadNormalMap();
			modelHandle = ModelManager::LoadObjectFile(fileName);
		}

		//transform��Get
		nlohmann::json& transform = object["transform"];
		TransformEular transformEular = GetTransform(transform);


		if (object.contains("children"))
		{
			nlohmann::json& child = object["children"];
			for (size_t i = 0; i < child.size(); i++)
			{
				std::string childType = child[i]["type"].get<string>();

				if (childType.compare("MESH") == 0)
				{
					LoadObj3dData(levelData, obj3dData, child[i]);
				}
				if (childType.compare("CAMERA") == 0)
				{
					LoadChildCameraData(levelData, obj3dData.get(), child[i]);
				}
			}
		}
		//�ۑ�
		obj3dData->Initialize(transformEular, objectDesc, modelHandle);
		levelData->obj3dData[objectName] = move(obj3dData);

	}

}

void SceneFileLoader::LoadCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object)
{
	shared_ptr<GameCameraData> cameraData;
	//object�̖��O
	string name = object["name"].get<string>();
	//transormGet
	TransformEular transformEular = GetTransform(object["transform"]);
    //�␳
	transformEular.rotate.x += 90.0f;
	//���W�A����ϊ�
	transformEular.rotate.x = transformEular.rotate.x * float(std::numbers::pi) / 180.0f;
	transformEular.rotate.y = transformEular.rotate.y * float(std::numbers::pi) / 180.0f;
	transformEular.rotate.z = transformEular.rotate.z * float(std::numbers::pi) / 180.0f;
	//data�쐬
	cameraData = make_shared<GameCameraData>();
	cameraData->SetObjName(name);
	cameraData->SetObjectType("CAMERA");
	cameraData->Create(transformEular);
	levelData->cameraData[name] = cameraData;
}

void SceneFileLoader::LoadChildCameraData(shared_ptr<LevelData>& levelData, IGameObjectData* data, nlohmann::json& object)
{
	shared_ptr<GameCameraData> cameraData;
	//object�̖��O
	string name = object["name"].get<string>();
	data->PushBackChildren(name);
	//transormGet
	TransformEular transformEular = GetTransform(object["transform"]);
	//�␳
	transformEular.rotate.x += 90.0f;
	//���W�A����ϊ�
	transformEular.rotate.x = transformEular.rotate.x * float(std::numbers::pi) / 180.0f;
	transformEular.rotate.y = transformEular.rotate.y * float(std::numbers::pi) / 180.0f;
	transformEular.rotate.z = transformEular.rotate.z * float(std::numbers::pi) / 180.0f;

	//data�쐬
	cameraData = make_shared<GameCameraData>();
	cameraData->SetObjName(name);
	cameraData->SetObjectType("CAMERA");
	cameraData->Create(transformEular);
	levelData->cameraData[name] = cameraData;
}

TransformEular SceneFileLoader::GetTransform(nlohmann::json transform)
{
	TransformEular transformEular;
	transformEular.translate.x = (float)transform["translate"][0];
	transformEular.translate.y = (float)transform["translate"][2];
	transformEular.translate.z = (float)transform["translate"][1];
	//rotate
	transformEular.rotate.x = -(float)transform["rotate"][0];
	transformEular.rotate.y = -(float)transform["rotate"][2];
	transformEular.rotate.z = -(float)transform["rotate"][1];
	//scale
	transformEular.scale.x = (float)transform["scale"][0];
	transformEular.scale.y = (float)transform["scale"][2];
	transformEular.scale.z = (float)transform["scale"][1];
	return transformEular;
}