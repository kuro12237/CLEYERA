#include "SceneFileLoader.h"

SceneFileLoader* SceneFileLoader::GetInstance()
{
	static SceneFileLoader instance;
	return &instance;
}

LevelData* SceneFileLoader::ReLoad(const string& filePath)
{

	ifstream file = FileLoader::JsonLoadFile("Resources/levelData/" + filePath);
	file >> deserialized;
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//sceneじゃなかった時エラーを吐く
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
	//memo
	//instancing描画かobject描画かの仕分けを作る

	if (objectType.compare("Player") == 0 || objectType.compare("Map") == 0)
	{
		string name = object["name"].get<string>();
		if (levelData->obj3dData.find(name) != levelData->obj3dData.end())
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
			//modelのファイル読み込み
			if (object.contains("file_name"))
			{
				string fileName = object["file_name"];
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

			//保存
			levelData->obj3dData[name] = move(obj3dData);
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
