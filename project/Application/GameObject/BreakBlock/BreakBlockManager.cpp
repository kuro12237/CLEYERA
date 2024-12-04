#include "BreakBlockManager.h"

void BreakBlockManager::Initialize()
{
	auto& transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();

	for (int i = 0; i < int(transforms.size()); i++)
	{
		shared_ptr<BreakBlock>block = make_shared<BreakBlock>();
		block->Initialize(name_, i);
		blocks_.push_back(move(block));
	}

	gameObjectManager_ = GameObjectManager::GetInstance();
}

void BreakBlockManager::Update()
{

	for (std::vector<std::shared_ptr<BreakBlock>>::iterator it = blocks_.begin(); it != blocks_.end();) {
		(*it)->Update();

		if ((*it)->GetIsDead()) {
			gameObjectManager_->GetObjInstancingData(name_)->GetTransforms()[(*it)->GetInstancingIndex()]->SetBreakFlag(true);
			it = blocks_.erase(it); // 削除後、次のイテレーターを取得
		}
		else {
			++it; // 削除しない場合のみインクリメント
		}
	}
}
