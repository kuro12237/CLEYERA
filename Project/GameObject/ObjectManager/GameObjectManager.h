#pragma once
#include"Utility/LevelData/LevelData.h"
#include"IObjectData.h"

class IObjectData;
class GameObjectManager
{
public:

	static GameObjectManager *GetInstance();

	/// <summary>
	/// levelData�̒��g���R�s�[
	/// </summary>
	/// <param name="data"></param>
	void CopyData(LevelData*data);

	/// <summary>
	/// �w�肵��obj���O�̃f�[�^���X�V
	/// </summary>
	/// <param name="name"></param>
	void ObjDataUpdate(IObjectData *data);

	/// <summary>
	/// �w�肵��Instancing���O�̃f�[�^���X�V
	/// </summary>
	/// <param name="name"></param>
	void InstancingObjDataUpdate(vector<shared_ptr<IGameInstancing3dObject>>data, string name);

	/// <summary>
	/// �w�肵�Ȃ��������̂̍X�V
	/// </summary>
	void Update();

	void Draw();

	void PushObj3dData(Game3dObjectData& data, string name) { obj3dData[name] = move(data); };

#pragma region Get

	Game3dObjectData& GetObj3dData(string name);

	Game3dInstancingObjectData& GetObjInstancingData(string name);

#pragma endregion

#pragma region Set

	void SetParent(string parentName, string childName);

#pragma endregion


private:

	vector<string>dataName_;
	vector<string>instancingDataName_;

	std::map<string, Game3dObjectData> obj3dData;
	std::map<string, Game3dInstancingObjectData>objInstancing3dData;

#pragma region singleton

	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const  GameObjectManager&) = delete;
	const  GameObjectManager& operator=(const GameObjectManager&) = delete;
#pragma endregion

};

