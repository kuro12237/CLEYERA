#pragma once
#include"Pch.h"
#include"FileLoader.h"
#include"Utility/LevelData/LevelData.h"
#include"Utility/CollisionManager/CollisionStructures/CollisionStructures.h"
#include"GameObject/GameCollider/ICollider.h"

class SceneFileLoader
{
public:

	static SceneFileLoader* GetInstance();

	shared_ptr<LevelData> ReLoad(const string& filePath);

private:

	AABB LoadCollider(nlohmann::json& object);


	void LoadMeshData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	void LoadObj3dData(shared_ptr<LevelData>& levelData, shared_ptr<Game3dObjectData>& data, nlohmann::json object);

	void LoadCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	void LoadChildCameraData(shared_ptr<LevelData>& levelData, shared_ptr<GameCameraData>& data, nlohmann::json& object);

	TransformEular GetTransform(nlohmann::json transform);

	nlohmann::json deserialized = nullptr;

	shared_ptr<LevelData> levelData = nullptr;
#pragma region 
	//Singleton
	SceneFileLoader() = default;
	~SceneFileLoader() = default;
	SceneFileLoader(const SceneFileLoader&) = delete;
	const SceneFileLoader& operator=(const SceneFileLoader&) = delete;
#pragma endregion 
};
