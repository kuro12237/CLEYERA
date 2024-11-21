#include "RailLoader.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

RailData RailLoader::LoadRail(const string& filePath)
{
	RailData result;
	const string kDirectoryFilePath_ = "Resources/LevelData/RailData/";
	ifstream  jsonData = FileLoader::JsonLoadFile(kDirectoryFilePath_ + filePath);

	nlohmann::json deserialized = nullptr;
	jsonData >> deserialized;
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//Rail‚¶‚á‚È‚©‚Á‚½ƒGƒ‰[‚ğ“f‚­
	string name = deserialized["name"].get<string>();
	assert(name.compare("Rail") == 0);

	assert(deserialized.contains("positions"));

	int index = 0;
	size_t size = deserialized["positions"].size();
	result.data.resize(size);

	for (nlohmann::json& object : deserialized["positions"])
	{
		result.data[index].Initialize();
		result.data[index].transform = GetWorldTransform(object["transform"]);
		if (index != 0)
		{
			result.data[index].SetParent(result.data[index - 1]);
		}

		index++;
	}

	for (size_t i = 0; i < result.data.size(); i++)
	{
		result.data[i].UpdateMatrix();

	}

	result.fileName = filePath;
	result.size = result.data.size();

	return result;
}

TransformEular RailLoader::GetWorldTransform(nlohmann::json transform)
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
