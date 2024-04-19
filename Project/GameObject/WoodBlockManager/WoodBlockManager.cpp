#include "WoodBlockManager.h"

void WoodBlockManager::Initialize()
{
	blocksGameObject_ = make_unique<GameInstancing3dObject>();
	blocksGameObject_->Create(BlockNum_, name_);

	uint32_t modelHandle = ModelManager::LoadObjectFile("TestBox");
	blocksGameObject_->SetModel(modelHandle);
	FileInitialize();
}

void WoodBlockManager::Update()
{


	for (int i = 0; i < blockCount_; i++)
	{
		if (blocks_[i])
		{
			GlobalVariables::GetInstance()->AddItem("WoodBlocks", "block" + kNumberString[i], blocksParam_[i]);
			blocksParam_[i]=GlobalVariables::GetInstance()->GetValue<TransformQua>("WoodBlocks", "block" + kNumberString[i]);
			blocks_[i]->SetTransformQua(blocksParam_[i]);
			blocks_[i]->Update();

			if (blocks_[i]->GetBreakFlag())
			{
				DeleateNumbersIndex_.push(i);
				blocks_[i].reset();
			}
		}
	}
	GlobalVariables::GetInstance()->SetValue(groupName, "blockCount", blockCount_);
	blocksGameObject_->Transfar();
}

void WoodBlockManager::Draw(const CameraData& camera)
{
	blocksGameObject_->Draw(camera);
}

void WoodBlockManager::UpdateImGui()
{
	ImGui::Text("blockCount %d", blockCount_);
	if (ImGui::Button("pushBlock::Block"))
	{
		TransformQua blockParam = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f,1.0f},{0.0f,0.5f,0.0f} };
		shared_ptr<WoodBlock> w = nullptr;
		w = make_shared<WoodBlock>();
		w->Initialize(blockParam);
		w->Update();
		blockCount_++;
		blocksParam_[blockCount_] = blockParam;
		w->SetNumber(blockCount_);
		blocks_.push_back(w);
		blocksGameObject_->PushVector(w, blockCount_);
	}

	for (int i = 0; i < blockCount_; i++)
	{
		if (blocks_[i]) {
			if (blocks_[i]->GetIsHit())
			{
				blocks_[i]->UpdateImGui();
			}
		}
	}
}

void WoodBlockManager::FileInitialize()
{
	blocksParam_.resize(128);
	GlobalVariables::GetInstance()->CreateGroup("WoodBlocks");
	blockCount_ = GlobalVariables::GetInstance()->GetValue<int32_t>(groupName, "blockCount");

	for (int i = 0; i < blockCount_; i++)
	{
		blocksParam_[i] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f,1.0f},{0.0f,0.5f,0.0f} };
		GlobalVariables::GetInstance()->AddItem("WoodBlocks", "block" + kNumberString[i],blocksParam_[i]);
		blocksParam_[i] = GlobalVariables::GetInstance()->GetValue<TransformQua>("WoodBlocks", "block" + kNumberString[i]);
		shared_ptr<WoodBlock> w = nullptr;
		w = make_shared<WoodBlock>();
		w->Initialize(blocksParam_[i]);
		w->SetNumber(i);
		blocks_.push_back(w);
		blocksGameObject_->PushVector(w, i);
	}
}
