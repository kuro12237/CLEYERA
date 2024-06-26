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
	}
	return levelData;
}

void SceneFileLoader::LoadMeshData(unique_ptr<LevelData>& levelData, nlohmann::json& object)
{
	Game3dObjectData obj3dData = {};
	Game3dInstancingObjectData obj3dInstancingData = {};

	string drawType = object["DrawType"].get<string>();
	string objectType = object["objectType"].get<string>();

	//通常表示
	if (drawType.compare("Normal") == 0)
	{
		string name = object["name"].get<string>();
		if (levelData->obj3dData.find(objectType) != levelData->obj3dData.end())
		{
			assert(0);
		}
		else
		{
			obj3dData.gameObject = make_unique<Game3dObject>();
			obj3dData.gameObject->Create(make_unique<Phong3dPipline>());

			obj3dData.worldTransform.Initialize();
			obj3dData.objectName = objectType;
			obj3dData.objectDesc.useLight = true;
			obj3dData.gameObject->SetDesc(obj3dData.objectDesc);
			//modelのファイル読み込み
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"].get<string>();
				ModelManager::ModelLoadNormalMap();
				obj3dData.modelHandle = ModelManager::LoadObjectFile(fileName);
				obj3dData.gameObject->SetModel(obj3dData.modelHandle);
			}

			//transformのGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//transform
			obj3dData.worldTransform.translate = transformEular.translate;
			obj3dData.worldTransform.rotation = transformEular.rotate;
			obj3dData.worldTransform.scale = transformEular.scale;
			obj3dData.worldTransform.UpdateMatrix();

			if (object.contains("children"))
			{
				nlohmann::json& child = object["children"];

				for (size_t i = 0; i < child.size(); i++)
				{
					LoadObj3dData(levelData, obj3dData, child[i]);
				}
			}
			//保存
			levelData->obj3dData[objectType] = move(obj3dData);
		}
	}
	//インスタンシング表示
	if (drawType.compare("Instancing") == 0)
	{
		if (levelData->objInstancing3dData.find(objectType) != levelData->objInstancing3dData.end())
		{
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();
			transforms->SetTransformEular(transformEular);
			transforms->Update();
			levelData->objInstancing3dData[objectType].transform_.push_back(transforms);
			uint32_t size = uint32_t(levelData->objInstancing3dData[objectType].transform_.size());
			levelData->objInstancing3dData[objectType].GameInstancingObject->PushVector(levelData->objInstancing3dData[objectType].transform_[size - 1], size);
		}
		else
		{
			//後でオブジェクトの合計数に換える
			const uint32_t instancingMax = 128;
			//インスタンスの生成
			obj3dInstancingData.objectType = objectType;
			obj3dInstancingData.GameInstancingObject = make_unique<GameInstancing3dObject>();
			obj3dInstancingData.GameInstancingObject->Create(instancingMax, objectType);

			//modelのファイル読み込み
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"];
				ModelManager::ModelLoadNormalMap();
				obj3dInstancingData.modelHandle = ModelManager::LoadObjectFile(fileName);
				obj3dInstancingData.GameInstancingObject->SetModel(obj3dInstancingData.modelHandle);
			}
			else
			{
				ModelManager::ModelLoadNormalMap();
				obj3dInstancingData.modelHandle = ModelManager::LoadObjectFile("DfCube");
				obj3dInstancingData.GameInstancingObject->SetModel(obj3dInstancingData.modelHandle);
			}
			//transformのGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//transform
			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();
			transforms->SetTransformEular(transformEular);
			transforms->Update();
			obj3dInstancingData.transform_.push_back(transforms);

			//保存
			levelData->objInstancing3dData[objectType] = move(obj3dInstancingData);

			uint32_t size = uint32_t(levelData->objInstancing3dData[objectType].transform_.size());
			levelData->objInstancing3dData[objectType].GameInstancingObject->PushVector(levelData->objInstancing3dData[objectType].transform_[size - 1], size);
		}
	}
}

void SceneFileLoader::LoadObj3dData(unique_ptr<LevelData>& levelData, Game3dObjectData& data, nlohmann::json object)
{
	Game3dObjectData obj3dData = {};
	Game3dInstancingObjectData obj3dInstancingData = {};

	string drawType = object["DrawType"].get<string>();
	string objectType = object["objectType"].get<string>();

	data.childName_.push_back(objectType);

	//通常表示
	if (drawType.compare("Normal") == 0)
	{
		string name = object["name"].get<string>();
		if (levelData->obj3dData.find(objectType) != levelData->obj3dData.end())
		{
			assert(0);
		}
		else
		{
			obj3dData.gameObject = make_unique<Game3dObject>();
			obj3dData.gameObject->Create(make_unique<Phong3dPipline>());

			obj3dData.worldTransform.Initialize();
			obj3dData.objectName = objectType;
			obj3dData.objectDesc.useLight = true;
			obj3dData.gameObject->SetDesc(obj3dData.objectDesc);
			//modelのファイル読み込み
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"].get<string>();
				ModelManager::ModelLoadNormalMap();
				obj3dData.modelHandle = ModelManager::LoadObjectFile(fileName);
				obj3dData.gameObject->SetModel(obj3dData.modelHandle);
			}

			//transformのGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//transform
			obj3dData.worldTransform.translate = transformEular.translate;
			obj3dData.worldTransform.rotation = transformEular.rotate;
			obj3dData.worldTransform.scale = transformEular.scale;
			obj3dData.worldTransform.UpdateMatrix();

			if (object.contains("children"))
			{
				nlohmann::json& child = object["children"];
				for (size_t i = 0; i < child.size(); i++)
				{
					LoadObj3dData(levelData, obj3dData, child[i]);
				}
			}
			//保存
			levelData->obj3dData[objectType] = move(obj3dData);
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
