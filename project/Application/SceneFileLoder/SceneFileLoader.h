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
	/// �t�@�C����ǂݍ��ݒ���
	/// </summary>
	shared_ptr<LevelData> ReLoad(const string& filePath);

private:

	/// <summary>
	/// �x�����烉�W�A���ɕϊ�
	/// </summary>
	Math::Vector::Vector3 degreesToRadians(Math::Vector::Vector3 degrees);

	/// <summary>
	/// box�̓����蔻��̓ǂݍ���
	/// </summary>
	AABB LoadCollider(nlohmann::json& object);

	/// <summary>
	/// ���b�V���̓ǂݍ���
	/// </summary>
	void LoadMeshData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	/// <summary>
	/// Object�̓ǂݍ���
	/// </summary>
	void LoadObj3dData(shared_ptr<LevelData>& levelData, shared_ptr<Game3dObjectData>& data, nlohmann::json object);
	
	/// <summary>
	/// �J�����ǂݍ���
	/// </summary>
	void LoadCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	/// <summary>
	/// �q�̃J�����ǂݍ���
	/// </summary>
	void LoadChildCameraData(shared_ptr<LevelData>& levelData, IGameObjectData* data, nlohmann::json& object);
	
	/// <summary>
	/// json����transform���Ƃ�
	/// </summary>
	TransformEular GetTransform(nlohmann::json transform);

	nlohmann::json deserialized = nullptr;
	shared_ptr<LevelData> levelData = nullptr;

	/// <summary>
	/// �u�����_�[����ǂݍ��񂾃J�����̕␳
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
