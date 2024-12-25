#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"BreakBlock.h"
#include"GameObject/ObjectInterface/IManagerList.h"

class BreakBlockManager :public IManagerList
{
public:
	BreakBlockManager() {};
	~BreakBlockManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

#pragma region Get
	vector<shared_ptr<BreakBlock>>GetBlocks() { return blocks_; }
#pragma endregion

private:

	string name_ = "BreakMap";

	vector<shared_ptr<BreakBlock>>blocks_;

	GameObjectManager* gameObjectManager_ = nullptr;
private:

};
