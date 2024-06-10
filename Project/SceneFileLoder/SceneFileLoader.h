#pragma once
#include"Pch.h"
#include"FileLoader.h"
#include"Utility/LevelData/LevelData.h"

class SceneFileLoader
{
public:
	
	static SceneFileLoader* GetInstance();

	unique_ptr<LevelData> ReLoad(const string& filePath);

private:

	Game3dObjectData  LoadGameObjectData(unique_ptr<LevelData>&levelData,nlohmann::json& object);

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
