#pragma once
#include"Pch.h"
#include"FileLoader.h"
#include"Utility/LevelData/LevelData.h"

class SceneFileLoader
{
public:
	
	static SceneFileLoader* GetInstance();

	void Initlaize();

	unique_ptr<LevelData> ReLoad(const string& filePath);

private:

	void LoadMeshData(unique_ptr<LevelData>  &levelData, nlohmann::json& object);

	TransformEular GetTransform(nlohmann::json transform);

	nlohmann::json deserialized = nullptr;


#pragma region 
	//Singleton
	SceneFileLoader() = default;
	~SceneFileLoader() = default;
	SceneFileLoader(const SceneFileLoader&) = delete;
	const SceneFileLoader& operator=(const SceneFileLoader&) = delete;
#pragma endregion 
};
