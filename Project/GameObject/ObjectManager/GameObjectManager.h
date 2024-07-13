#pragma once
#include"Utility/LevelData/LevelData.h"
#include"IObjectData.h"

class IObjectData;
class GameObjectManager
{
public:

	static GameObjectManager* GetInstance();

	/// <summary>
	/// levelDataの中身をコピー
	/// </summary>
	/// <param name="data"></param>
	void CopyData(LevelData* data);

	/// <summary>
	/// 作ったすべてのものに親子関係があるチェックあったら親子関係をつける
	/// </summary>
	void SetAllParents();

#pragma region Update

	/// <summary>
	/// 指定しなかったものの更新
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
	const shared_ptr<Game3dObjectData>& GetObj3dData_ptr(string name) { return obj3dData_[name]; }
	std::map<string, shared_ptr<Game3dObjectData>>& GetObj3dDatas() { return obj3dData_; }

	shared_ptr<GameCameraData>& GetCameraData(string name) { return cameraData_[name]; }

	shared_ptr<Game3dInstancingObjectData>& GetObjInstancingData(string name);

#pragma endregion

#pragma region Set

	void SetParent(string parentName, string childName);

	void CameraReset(string name="");

#pragma endregion


private:

	void checkChildren(shared_ptr<Game3dObjectData>& data);

	string inputTextSelectCamera_ = "";

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

