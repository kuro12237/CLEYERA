#pragma once
#include"Utility/LevelData/LevelData.h"
#include"Utility/FileLoader/FileLoader.h"

struct RailData
{
	vector<Engine::Transform::WorldTransform>data;
	size_t size = 0;
	string fileName = "";
};

class RailLoader
{
public:

	static RailData LoadRail(const string& filePath);

private:
	static TransformEular GetWorldTransform(nlohmann::json transform);
};

