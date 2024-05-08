#pragma once

#include"WoodBlock.h"
#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Utility/NumberString/NumberString.h"
#include"Utility/GlobalVariables/GlobalVariables.h"


class WoodBlockManager
{
public:
	WoodBlockManager() {};
	~WoodBlockManager() {};

	void Initialize();

	void Update();

	void Draw(const CameraData &camera);

	vector<shared_ptr<WoodBlock>>GetBlocks() { return blocks_; }

	void UpdateImGui();

private:

	void FileInitialize();

	const string name_ = "WoodBlockManager";
	const string groupName ="WoodBlocks";
	const uint32_t Height_ = 8;
	const uint32_t Width_ = 16;

	const uint32_t BlockNum_ = Height_*Width_;

	unique_ptr<GameInstancing3dObject>blocksGameObject_ = nullptr;

	vector<shared_ptr<WoodBlock>>blocks_;
	vector<TransformQua>blocksParam_ = {};
	vector<bool>blockFlag_ = {};
	std::queue<uint32_t>DeleateNumbersIndex_ = {};

	int32_t blockCount_ = 5;
	queue<uint32_t>checkBlockIndex{};
};