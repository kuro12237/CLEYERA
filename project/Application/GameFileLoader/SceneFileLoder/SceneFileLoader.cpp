#include "SceneFileLoader.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

SceneFileLoader* SceneFileLoader::GetInstance()
{
	static SceneFileLoader instance;
	return &instance;
}

shared_ptr<LevelData> SceneFileLoader::ReLoad(const string& filePath)
{
	ifstream file = FileLoader::JsonLoadFile("Resources/levelData/StageData/" + filePath);
	file >> deserialized;
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//sceneじゃなかった時エラーを吐く
	string name = deserialized["name"].get<string>();
	assert(name.compare("scene") == 0);

	if (!levelData_)
	{
		levelData_ = make_shared<LevelData>();
	}

	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));

		std::string type = object["type"].get<string>();

		if (isTypeCompare(type, "MESH"))
		{
			LoadObj3dData(levelData_, object);
		}

		if (isTypeCompare(type, "CAMERA"))
		{
			LoadChildCameraData(levelData_, object);
		}
	}
	return levelData_;
}

bool SceneFileLoader::isTypeCompare(const string& type, const string& name)
{
	if (type.compare(name) == 0)
	{
		return true;
	}
	return false;
}

bool SceneFileLoader::CheckJsonObjectContains(nlohmann::json& object, string name)
{
	if (object.contains(name))
	{
		return true;
	}
	return false;
}

uint32_t SceneFileLoader::LoadModelData(nlohmann::json& object, shared_ptr<Game3dObjectData> data)
{
	uint32_t modelHandle = 0;
	std::string modelFileName;
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
		data->SetModelFilePath(fileName);
		data->SetObjectType("ARMATURE");
	}
	return modelHandle;
}

vector<string> SceneFileLoader::GetParamFileNames(nlohmann::json& object)
{
	vector<string> datas;
	const auto& paramFileNames = object["paramFileNames"];
	for (auto it = paramFileNames.begin(); it != paramFileNames.end(); ++it) {
		string fileKey = it.key();
		string fileName = it.value().get<string>();

		datas.push_back(fileName);
	}

	return datas;
}

Math::Vector::Vector3 SceneFileLoader::degreesToRadians(Math::Vector::Vector3 degrees)
{
	return Math::Vector::Vector3(degrees.x * static_cast<float>(numbers::pi) / 180.0f, degrees.y * static_cast<float>(numbers::pi) / 180.0f, degrees.z * static_cast<float>(numbers::pi) / 180.0f);
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

void SceneFileLoader::LoadObj3dData(shared_ptr<LevelData>& levelData, nlohmann::json object, shared_ptr<Game3dObjectData> data)
{
	shared_ptr<Game3dObjectData> obj3dData = {};
	shared_ptr<Game3dInstancingObjectData> obj3dInstancingData = {};

	string drawType = object["DrawType"].get<string>();
	string objectName = object["name"].get<string>();
	uint32_t modelHandle = 0;

	if (data)
	{
		data->PushBackChildren(objectName);
	}

	//通常表示
	if (drawType.compare("Normal") == 0)
	{
		obj3dData = make_shared<Game3dObjectData>();
		obj3dData->SetObjName(objectName);
		obj3dData->SetObjectType("MESH");

		std::string modelFileName;
		Game3dObjectDesc objectDesc;

		vector<string>childName;

		objectDesc.useLight = true;
		//modelのファイル読み込み

		if (CheckJsonObjectContains(object, "file_name"))
		{
			modelHandle = LoadModelData(object, obj3dData);
		}

		//transformのGet
		nlohmann::json& transform = object["transform"];
		TransformEular transformEular = GetTransform(transform);
		transformEular.rotate = degreesToRadians(transformEular.rotate);

		if (CheckJsonObjectContains(object, "paramFileNames"))
		{
			vector<string>fileNames = GetParamFileNames(object);

			for (const string& fileName : fileNames)
			{
				obj3dData->PushBackParamFilePath(fileName + ".json");
			}
		}

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
				std::string childType = child[i]["type"].get<string>();

				if (childType.compare("MESH") == 0)
				{
					LoadObj3dData(levelData, child[i], obj3dData);
				}
				if (childType.compare("CAMERA") == 0)
				{
					LoadChildCameraData(levelData, child[i], obj3dData.get());
				}
			}
		}
		//保存
		obj3dData->Initialize(transformEular, objectDesc, modelHandle);
		levelData->obj3dData[objectName] = move(obj3dData);
	}
	//インスタンシング表示
	if (drawType.compare("Instancing") == 0)
	{
		string objectINstancingGrop = object["InstancingObjName"].get<string>();
		if (levelData->objInstancing3dData.find(objectINstancingGrop) != levelData->objInstancing3dData.end())
		{

			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();

			//transformGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//回転をラジアンに変換
			transformEular.rotate = degreesToRadians(transformEular.rotate);

			if (object.contains("collider"))
			{
				AABB aabb = LoadCollider(object["collider"]);
				aabb.max = Math::Vector::Multiply(transformEular.scale, aabb.max);
				aabb.min = Math::Vector::Multiply(transformEular.scale, aabb.min);

				transforms->SetAABB(aabb);
			}

			transforms->SetTransformEular(transformEular);
			transforms->Update();
			levelData->objInstancing3dData[objectINstancingGrop]->PushBackTransform(transforms);
			transforms->GetName() = objectName;

			uint32_t size = uint32_t(levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms().size());

			levelData->objInstancing3dData[objectINstancingGrop]->PushObjectData(
				levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms()[size - 1], size);
		}
		else
		{
			//インスタンスの生成
			obj3dInstancingData = make_shared<Game3dInstancingObjectData>();

			//modelのファイル読み込み
			if (CheckJsonObjectContains(object, "file_name"))
			{
				modelHandle = LoadModelData(object, obj3dData);
			}

			obj3dInstancingData->Initialize(objectINstancingGrop, modelHandle);

			shared_ptr<IGameInstancing3dObject> transforms = make_shared<IGameInstancing3dObject>();

			//transformのGet
			nlohmann::json& transform = object["transform"];
			TransformEular transformEular = GetTransform(transform);
			//回転をラジアンに変換
			transformEular.rotate = degreesToRadians(transformEular.rotate);

			transforms->SetTransformEular(transformEular);

			if (object.contains("collider"))
			{
				AABB aabb = LoadCollider(object["collider"]);
				aabb.max = Math::Vector::Multiply(transformEular.scale, aabb.max);
				aabb.min = Math::Vector::Multiply(transformEular.scale, aabb.min);

				transforms->SetAABB(aabb);
			}


			transforms->GetName() = objectName;

			transforms->Update();

			obj3dInstancingData->PushBackTransform(transforms);
			//保存
			levelData->objInstancing3dData[objectINstancingGrop] = move(obj3dInstancingData);

			uint32_t size = uint32_t(levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms().size());
			levelData->objInstancing3dData[objectINstancingGrop]->PushObjectData(
				levelData->objInstancing3dData[objectINstancingGrop]->GetTransforms()[size - 1], size);

			if (object.contains("children"))
			{
				nlohmann::json& child = object["children"];

				for (size_t i = 0; i < child.size(); i++)
				{
					std::string type = child[i]["type"].get<string>();

					if (type.compare("MESH") == 0)
					{
						LoadObj3dData(levelData, child[i], obj3dData);
					}
					if (type.compare("CAMERA") == 0)
					{
						LoadChildCameraData(levelData, child[i], obj3dData.get());
					}
				}
			}
		}
	}
}

void SceneFileLoader::LoadCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object)
{
	shared_ptr<GameCameraData> cameraData;
	//objectの名前
	string name = object["name"].get<string>();
	//transormGet
	TransformEular transformEular = GetTransform(object["transform"]);
	//補正
	transformEular.rotate.x += 90.0f;
	//回転をラジアンに変換
	transformEular.rotate = degreesToRadians(transformEular.rotate);

	//data作成
	cameraData = make_shared<GameCameraData>();
	cameraData->SetObjName(name);
	cameraData->SetObjectType("CAMERA");
	cameraData->Create(transformEular);
	levelData->cameraData[name] = cameraData;
}

void SceneFileLoader::LoadChildCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object, IGameObjectData* data)
{
	shared_ptr<GameCameraData> cameraData;
	//objectの名前
	string name = object["name"].get<string>();

	//parentData
	if (data)
	{
		data->PushBackChildren(name);
	}

	//transormGet
	TransformEular transformEular = GetTransform(object["transform"]);
	//補正
	transformEular.rotate.x += 90.0f;
	//ラジアン二変換
	transformEular.rotate.x = transformEular.rotate.x * float(std::numbers::pi) / 180.0f;
	transformEular.rotate.y = transformEular.rotate.y * float(std::numbers::pi) / 180.0f;
	transformEular.rotate.z = transformEular.rotate.z * float(std::numbers::pi) / 180.0f;


	//data作成
	cameraData = make_shared<GameCameraData>();

	if (CheckJsonObjectContains(object, "paramFileNames"))
	{
		vector<string>fileNames = GetParamFileNames(object);

		for (const string& fileName : fileNames)
		{
			cameraData->PushBackParamFilePath(fileName + ".json");
		}
	}

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
