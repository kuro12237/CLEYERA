#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Block.h"

/// <summary>
/// ブロック管理
/// </summary>
class BlockManager
{
public:
	BlockManager() {};
	~BlockManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Get
	vector<shared_ptr<Block>>GetBlocks() { return blocks_; }
#pragma endregion

private:

	string name_ = "Map";

	vector<shared_ptr<Block>>blocks_;

	bool isInitialize = false;


};

