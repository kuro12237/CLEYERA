#pragma once
#include"Utility/LevelData/LevelData.h"
#include"IObjectData.h"

class IObjectData;
class GameObjectManager
{
public:
	GameObjectManager() {};
	~GameObjectManager() {};

	/// <summary>
	/// levelDataの中身をコピー
	/// </summary>
	/// <param name="data"></param>
	void CopyData(LevelData*data);

	/// <summary>
	/// 指定したobj名前のデータを更新
	/// </summary>
	/// <param name="name"></param>
	void ObjDataUpdate(IObjectData *data);

	/// <summary>
	/// 指定したInstancing名前のデータを更新
	/// </summary>
	/// <param name="name"></param>
	void InstancingObjDataUpdate(vector<shared_ptr<IGameInstancing3dObject>>data, string name);

	/// <summary>
	/// 指定しなかったものの更新
	/// </summary>
	void Update();

	void Draw();

#pragma region Get

	Game3dObjectData& GetObj3dData(string name);

	Game3dInstancingObjectData& GetObjInstancingData(string name);

#pragma endregion


private:

	vector<string>dataName_;
	vector<string>instancingDataName_;

	std::map<string, Game3dObjectData> obj3dData;
	std::map<string, Game3dInstancingObjectData>objInstancing3dData;

};

