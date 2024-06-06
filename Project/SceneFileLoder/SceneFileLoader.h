#pragma once
#include"Pch.h"
#include"FileLoader.h"
#include"Utility/LevelData/LevelData.h"

class SceneFileLoader
{
public:
	
	static SceneFileLoader* GetInstance();

	void Initlaize();

	LevelData* ReLoad(const string& filePath);

private:
	nlohmann::json deserialized = nullptr;

	void LoadMeshData(LevelData* levelData, nlohmann::json& object);

	TransformEular GetTransform(nlohmann::json transform);

#pragma region 
	//Singleton
	SceneFileLoader() = default;
	~SceneFileLoader() = default;
	SceneFileLoader(const SceneFileLoader&) = delete;
	const SceneFileLoader& operator=(const SceneFileLoader&) = delete;
#pragma endregion 
};
