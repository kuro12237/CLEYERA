#include "SceneFileLoader.h"

SceneFileLoader* SceneFileLoader::GetInstance()
{
	static SceneFileLoader instance;
	return &instance;
}

unique_ptr<LevelData> SceneFileLoader::ReLoad(const string& filePath)
{

	ifstream file = FileLoader::JsonLoadFile("Resources/levelData/" + filePath);
	file >> deserialized;
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//sceneじゃなかった時エラーを吐く
	string name = deserialized["name"].get<string>();
	assert(name.compare("scene") == 0);

	unique_ptr<LevelData>  levelData = make_unique<LevelData>();


	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));

		std::string type = object["type"].get<string>();

		if (type.compare("MESH") == 0)
		{
			LoadMeshData(levelData, object);
		}

		if (type.compare("Camera")==0)
		{
			LoadCameraData(levelData, object);
		}


	}
	return levelData;
}

void SceneFileLoader::LoadMeshData(unique_ptr<LevelData>& levelData, nlohmann::json& object)
{
	shared_ptr<Game3dObjectData> obj3dData = {};
	shared_ptr<Game3dInstancingObjectData> obj3dInstancingData = {};

	string drawType = object["DrawType"].get<string>();
	string objectName = object["name"].get<string>();
	uint32_t modelHandle = 0;

	//通常表示
	if (drawType.compare("Normal") == 0)
	{
		string name = object["name"].get<string>();
		if (levelData->obj3dData.find(objectName) != levelData->obj3dData.end())
		{
			assert(0);
		}
		else
		{
			obj3dData = make_shared<Game3dObjectData>();

			obj3dData->SetObjName(objectName);

			std::string modelFileName;
			Game3dObjectDesc objectDesc;
			vector<string>childName;

			objectDesc.useLight = true;

			//modelのファイル読み込み
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"].get<string>();
				ModelManager::ModelLoadNormalMap();
				modelHandle = ModelManager::LoadObjectFile(fileName);
			}

			//transformのGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//transform

			if (object.contains("children"))
			{
				nlohmann::json& child = object["children"];

				for (size_t i = 0; i < child.size(); i++)
				{
					LoadObj3dData(levelData, obj3dData, child[i]);
				}
			}
			//保存
			obj3dData->Initialize(transformEular, objectDesc, modelHandle);

			levelData->obj3dData[objectName] = move(obj3dData);
		}
	}
	//インスタンシング表示
	if (drawType.compare("Instancing") == 0)
	{
		string objectINstancingGrop = object["instancingObjName"].get<string>();
		if (levelData->objInstancing3dData.find(objectINstancingGrop) != levelData->objInstancing3dData.end())
		{
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();
			transforms->SetTransformEular(transformEular);
			transforms->Update();
			levelData->objInstancing3dData[objectINstancingGrop]->PushBackTransform(transforms);

			uint32_t size = uint32_t(levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms().size());

			levelData->objInstancing3dData[objectINstancingGrop]->PushObjectData(
				levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms()[size - 1], size);
		}
		else
		{
			//インスタンスの生成
			obj3dInstancingData = make_shared<Game3dInstancingObjectData>();

			//modelのファイル読み込み
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

			//transformのGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//transform
			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();
			transforms->SetTransformEular(transformEular);
			transforms->Update();
			obj3dInstancingData->PushBackTransform(transforms);
			//保存
			levelData->objInstancing3dData[objectINstancingGrop] = move(obj3dInstancingData);

			uint32_t size = uint32_t(levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms().size());
			levelData->objInstancing3dData[objectINstancingGrop]->PushObjectData(
				levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms()[size - 1], size);
		}
	}
}

void SceneFileLoader::LoadObj3dData(unique_ptr<LevelData>& levelData, shared_ptr<Game3dObjectData>& data, nlohmann::json object)
{
	shared_ptr<Game3dObjectData> obj3dData = {};
	shared_ptr<Game3dInstancingObjectData> obj3dInstancingData = {};

	string drawType = object["DrawType"].get<string>();
	string objectName = object["name"].get<string>();

	data->PushBackChildren(objectName);

	//通常表示
	if (drawType.compare("Normal") == 0)
	{
		string name = object["name"].get<string>();
		if (levelData->obj3dData.find(objectName) != levelData->obj3dData.end())
		{
			assert(0);
		}
		else
		{
			obj3dData = make_shared<Game3dObjectData>();
			obj3dData->SetObjName(objectName);

			std::string modelFileName;
			Game3dObjectDesc objectDesc;
			uint32_t modelHandle = 0;
			vector<string>childName;

			objectDesc.useLight = true;
			//modelのファイル読み込み
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"].get<string>();
				ModelManager::ModelLoadNormalMap();
				modelHandle = ModelManager::LoadObjectFile(fileName);
			}

			//transformのGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
	

			if (object.contains("children"))
			{
				nlohmann::json& child = object["children"];
				for (size_t i = 0; i < child.size(); i++)
				{
					LoadObj3dData(levelData, obj3dData, child[i]);
				}
			}
			//保存
			obj3dData->Initialize(transformEular, objectDesc, modelHandle);
			levelData->obj3dData[objectName] = move(obj3dData);
		}
	}

}

void SceneFileLoader::LoadCameraData(unique_ptr<LevelData>& levelData, nlohmann::json& object)
{
	GameCameraData data;
	object, levelData;


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
