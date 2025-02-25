#pragma once
#include"Pch.h"
#include"FileLoader.h"
#include"Utility/LevelData/LevelData.h"
#include"GameObject/GameCollider/Collider.h"
#include"GameObject/GameCollider/ColliderData.h"

/// <summary>
///  LevelDataを読むクラス
/// </summary>
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
	/// typeを識別する関数
	/// </summary>
	bool isTypeCompare(const string& type, const string& name);

	/// <summary>
	/// jsonの中に指定した名前の物が入っているかを判断する関数
	/// </summary>
	bool CheckJsonObjectContains(nlohmann::json& object, string name);

	/// <summary>
	/// モデル読み込み関数
	/// </summary>
	/// <param name="json"></param>
	/// <param name="ObjectData"></param>
	/// <returns></returns>
	uint32_t  LoadModelData(nlohmann::json& object, shared_ptr<Game3dObjectData> data);

	/// <summary>
	/// オブジェクトのパラメーター読み込み関数
	/// </summary>
	/// <param name="object"></param>
	/// <returns></returns>
	vector<string>GetParamFileNames(nlohmann::json& object);

	/// <summary>
	/// 度数からラジアンに変換
	/// </summary>
	Math::Vector::Vector3 degreesToRadians(Math::Vector::Vector3 degrees);

	/// <summary>
	/// boxの当たり判定の読み込み
	/// </summary>
	AABB LoadCollider(nlohmann::json& object);

	/// <summary>
	/// Objectの読み込み
	/// </summary>
	void LoadObj3dData(shared_ptr<LevelData>& levelData, nlohmann::json object, shared_ptr<Game3dObjectData> data = nullptr);

	/// <summary>
	/// カメラ読み込み
	/// </summary>
	void LoadCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	/// <summary>
	/// 子のカメラ読み込み
	/// </summary>
	void LoadChildCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object, IGameObjectData* data = nullptr);

	/// <summary>
	/// jsonからtransformをとる
	/// </summary>
	Engine::Transform::TransformEular GetTransform(nlohmann::json transform);

	nlohmann::json deserialized = nullptr;
	shared_ptr<LevelData> levelData_ = nullptr;

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
