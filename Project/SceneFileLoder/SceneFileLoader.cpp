#include "SceneFileLoader.h"

SceneFileLoader* SceneFileLoader::GetInstance()
{
	static SceneFileLoader instance;
	return &instance;
}

LevelData* SceneFileLoader::ReLoad(const string& filePath)
{


	ifstream file = FileLoader::JsonLoadFile(filePath);
	file >> deserialized;
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//scene����Ȃ��������G���[��f��
	string name = deserialized["name"].get<string>();
	assert(name.compare("scene") == 0);

	LevelData* levelData = new LevelData();


	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));

		std::string type = object["type"].get<string>();
		if (type.compare("MESH") == 0)
		{
			LoadMeshData(levelData, object);
		}
	}
	return levelData;
}

void SceneFileLoader::LoadMeshData(LevelData* levelData, nlohmann::json& object)
{
	Game3dObjectData obj3dData = {};
	Game3dInstancingObjectData obj3dInstancingData = {};

	string objectType = object["objectType"].get<string>();
	string fileName = object["file_name"].get<string>();

	if (objectType.compare("Player") == 0)
	{
		if (levelData->obj3dData.find(objectType) != levelData->obj3dData.end())
		{
			assert(0);
		}
		else
		{
			obj3dData.gameObject = make_unique<Game3dObject>();
			obj3dData.gameObject->Create(make_unique<Phong3dPipline>());

			obj3dData.worldTransform.Initialize();

			obj3dData.objectDesc.useLight = true;
			obj3dData.gameObject->SetDesc(obj3dData.objectDesc);
			//model�̃t�@�C���ǂݍ���
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"];
				obj3dData.modelHandle = ModelManager::LoadObjectFile(fileName);
				obj3dData.gameObject->SetModel(obj3dData.modelHandle);
			}

			//transform��Get
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//transform
			obj3dData.worldTransform.translate = transformEular.translate;
			obj3dData.worldTransform.rotation = transformEular.rotate;
			obj3dData.worldTransform.scale = transformEular.scale;
			obj3dData.worldTransform.UpdateMatrix();

			//�ۑ�
			levelData->obj3dData[objectType] = move(obj3dData);
		}

	}


	if (objectType.compare("Map") == 0)
	{
		if (levelData->objInstancing3dData.find(objectType) != levelData->objInstancing3dData.end())
		{
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();
			transforms->SetTransformEular(transformEular);
			transforms->Update();
			levelData->objInstancing3dData[objectType].transform_.push_back(transforms);
		}
		else
		{
			//��ŃI�u�W�F�N�g�̍��v���Ɋ�����
			const uint32_t instancingMax = 128;
			//�C���X�^���X�̐���
			obj3dInstancingData.objectType = objectType;
			obj3dInstancingData.GameInstancingObject = make_unique<GameInstancing3dObject>();
			obj3dInstancingData.GameInstancingObject->Create(instancingMax, objectType);

			//model�̃t�@�C���ǂݍ���
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"];
				ModelManager::ModelLoadNormalMap();
				obj3dInstancingData.modelHandle = ModelManager::LoadObjectFile(fileName);
				obj3dInstancingData.GameInstancingObject->SetModel(obj3dInstancingData.modelHandle);
			}

			//transform��Get
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//transform
			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();
			transforms->SetTransformEular(transformEular);
			transforms->Update();
			obj3dInstancingData.transform_.push_back(transforms);
			//�ۑ�
			levelData->objInstancing3dData[objectType] = move(obj3dInstancingData);
		}
	}

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