#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Block.h"

/// <summary>
/// �u���b�N�Ǘ�
/// </summary>
class BlockManager
{
public:
	BlockManager() {};
	~BlockManager() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
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

