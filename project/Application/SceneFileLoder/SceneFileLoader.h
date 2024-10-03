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

	/// <summary>
	/// ファイルを読み込み直す
	/// </summary>
	shared_ptr<LevelData> ReLoad(const string& filePath);

private:

	/// <summary>
	/// 度数からラジアンに変換
	/// </summary>
	Math::Vector::Vector3 degreesToRadians(Math::Vector::Vector3 degrees);

	/// <summary>
	/// boxの当たり判定の読み込み
	/// </summary>
	AABB LoadCollider(nlohmann::json& object);

	/// <summary>
	/// メッシュの読み込み
	/// </summary>
	void LoadMeshData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	/// <summary>
	/// Objectの読み込み
	/// </summary>
	void LoadObj3dData(shared_ptr<LevelData>& levelData, shared_ptr<Game3dObjectData>& data, nlohmann::json object);
	
	/// <summary>
	/// カメラ読み込み
	/// </summary>
	void LoadCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	/// <summary>
	/// 子のカメラ読み込み
	/// </summary>
	void LoadChildCameraData(shared_ptr<LevelData>& levelData, IGameObjectData* data, nlohmann::json& object);
	
	/// <summary>
	/// jsonからtransformをとる
	/// </summary>
	TransformEular GetTransform(nlohmann::json transform);

	nlohmann::json deserialized = nullptr;
	shared_ptr<LevelData> levelData = nullptr;

	/// <summary>
	/// ブレンダーから読み込んだカメラの補正
	/// </summary>
	const float CameraRotationOffsetX = 90.0f;

#pragma region
	//Singleton
	SceneFileLoader() = default;
	~SceneFileLoader() = default;
	SceneFileLoader(const SceneFileLoader&) = delete;
	const SceneFileLoader& operator=(const SceneFileLoader&) = delete;
#pragma endregion 
};
