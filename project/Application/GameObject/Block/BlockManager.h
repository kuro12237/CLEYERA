#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"Block.h"

class BlockManager
{
public:

	BlockManager() {};
	~BlockManager() {};

	void Initialize();

	void Update();

	vector<shared_ptr<Block>>GetBlocks() { return blocks_; }

private:

	string name_ = "Map";

	vector<shared_ptr<Block>>blocks_;

	bool isInitialize = false;


};

