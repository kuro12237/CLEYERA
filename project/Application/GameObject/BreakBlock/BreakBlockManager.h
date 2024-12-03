#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"BreakBlock.h"

class BreakBlockManager
{
public:
	BreakBlockManager() {};
	~BreakBlockManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Get
	vector<shared_ptr<BreakBlock>>GetBlocks() { return blocks_; }
#pragma endregion

private:

	string name_ = "BreakMap";

	vector<shared_ptr<BreakBlock>>blocks_;

private:

};
