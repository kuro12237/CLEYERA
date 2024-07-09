#pragma once
#include"Utility/LevelData/LevelData.h"
#include"IObjectData.h"

class IObjectData;
class GameObjectManager
{
public:

	static GameObjectManager* GetInstance();

	/// <summary>
	/// levelData�̒��g���R�s�[
	/// </summary>
	/// <param name="data"></param>
	void CopyData(LevelData* data);

	/// <summary>
	/// ��������ׂĂ̂��̂ɐe�q�֌W������`�F�b�N��������e�q�֌W������
	/// </summary>
	void SetAllParents();

#pragma region Update

	/// <summary>
	/// �w�肵��obj���O�̃f�[�^���X�V
	/// </summary>
	/// <param name="name"></param>
	void ObjDataUpdate(IObjectData* data);

	/// <summary>
	/// �w�肵��Instancing���O�̃f�[�^���X�V
	/// </summary>
	/// <param name="name"></param>
	void InstancingObjDataUpdate(vector<shared_ptr<IGameInstancing3dObject>>data, string name);

	void CameraUpdate(IObjectData* data);

	/// <summary>
	/// �w�肵�Ȃ��������̂̍X�V
	/// </summary>
	void Update();

	void ImGuiUpdate();

#pragma endregion

	void Draw();

	void PushObj3dData(shared_ptr<Game3dObjectData>& data, string name) { obj3dData_[name] = move(data); };

	void ClearObj3dData(string name) { obj3dData_.erase(name); }

	void ClearAllData();

#pragma region Get

	shared_ptr<Game3dObjectData>& GetObj3dData(string name);

	shared_ptr<Game3dInstancingObjectData>& GetObjInstancingData(string name);

#pragma endregion

#pragma region Set

	void SetParent(string parentName, string childName);

	void CameraReset(string name);

#pragma endregion


private:

	void checkChildren(shared_ptr<Game3dObjectData>& data);

	vector<string>dataName_;
	vector<string>instancingDataName_;

	std::map<string, shared_ptr<Game3dObjectData>> obj3dData_;
	std::map<string, shared_ptr<Game3dInstancingObjectData>>objInstancing3dData_;
	std::map<string, shared_ptr<GameCameraData>>cameraData_;

#pragma region singleton

	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const  GameObjectManager&) = delete;
	const  GameObjectManager& operator=(const GameObjectManager&) = delete;
#pragma endregion

};

