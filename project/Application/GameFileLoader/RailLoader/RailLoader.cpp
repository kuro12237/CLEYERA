#include "RailLoader.h"

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

	//RailÇ∂Ç·Ç»Ç©Ç¡ÇΩéûÉGÉâÅ[ÇìfÇ≠
	string name = deserialized["name"].get<string>();
	assert(name.compare("Rail") == 0);

	assert(deserialized.contains("positions"));

	for (nlohmann::json& object : deserialized["positions"])
	{
		result.data.push_back(GetWorldTransform(object["transform"]));
	}

	result.fileName = filePath;
	result.size = result.data.size() - 1;

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
