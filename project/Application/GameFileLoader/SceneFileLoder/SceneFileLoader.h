#pragma once
#include"Pch.h"
#include"FileLoader.h"
#include"Utility/LevelData/LevelData.h"
#include"GameObject/GameCollider/ICollider.h"
#include"GameObject/GameCollider/ColliderData.h"

/// <summary>
///  LevelData��ǂރN���X
/// </summary>
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
	/// type�����ʂ���֐�
	/// </summary>
	bool isTypeCompare(const string& type, const string& name);

	/// <summary>
	/// json�̒��Ɏw�肵�����O�̕��������Ă��邩�𔻒f����֐�
	/// </summary>
	bool CheckJsonObjectContains(nlohmann::json& object, string name);

	/// <summary>
	/// ���f���ǂݍ��݊֐�
	/// </summary>
	/// <param name="json"></param>
	/// <param name="ObjectData"></param>
	/// <returns></returns>
	uint32_t  LoadModelData(nlohmann::json& object, shared_ptr<Game3dObjectData> data);

	/// <summary>
	/// �I�u�W�F�N�g�̃p�����[�^�[�ǂݍ��݊֐�
	/// </summary>
	/// <param name="object"></param>
	/// <returns></returns>
	vector<string>GetParamFileNames(nlohmann::json& object);

	/// <summary>
	/// �x�����烉�W�A���ɕϊ�
	/// </summary>
	Math::Vector::Vector3 degreesToRadians(Math::Vector::Vector3 degrees);

	/// <summary>
	/// box�̓����蔻��̓ǂݍ���
	/// </summary>
	AABB LoadCollider(nlohmann::json& object);

	/// <summary>
	/// Object�̓ǂݍ���
	/// </summary>
	void LoadObj3dData(shared_ptr<LevelData>& levelData, nlohmann::json object, shared_ptr<Game3dObjectData> data = nullptr);

	/// <summary>
	/// �J�����ǂݍ���
	/// </summary>
	void LoadCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object);

	/// <summary>
	/// �q�̃J�����ǂݍ���
	/// </summary>
	void LoadChildCameraData(shared_ptr<LevelData>& levelData, nlohmann::json& object, IGameObjectData* data = nullptr);

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
