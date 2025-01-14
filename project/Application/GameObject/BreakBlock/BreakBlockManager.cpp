#include "BreakBlockManager.h"

void BreakBlockManager::Initialize()
{

	gameObjectManager_ = GameObjectManager::GetInstance();
	const string name = "BreakBlockMap";

	uint32_t enemyCount = 0;

	for (uint32_t Count_ = 0; Count_ < uint32_t(gameObjectManager_->GetObj3dDatas().size()); Count_++)
	{
		string count = to_string(enemyCount);

		string enemyName = "";
		if (count == "0")
		{
			enemyName = name;
		}
		else {
			enemyName = name + "." + string(3 - to_string(enemyCount).length(), '0') + to_string(enemyCount);
		}

		if (gameObjectManager_->GetObj3dDatas().find(enemyName) != gameObjectManager_->GetObj3dDatas().end())
		{
			auto obj = gameObjectManager_->GetObj3dData(enemyName);

			shared_ptr<BreakBlock>breakBlock = nullptr;
			breakBlock = make_shared<BreakBlock>();
			breakBlock->INameable::SetName(enemyName);
			breakBlock->SetName(enemyName);
			breakBlock->SetInstanceINdex(enemyCount);
			breakBlock->Initialize();

			blocks_.push_back(breakBlock);
			enemyCount++;
		}
		else
		{
			break;
		}
	}

}

void BreakBlockManager::Update()
{

	for (std::vector<std::shared_ptr<BreakBlock>>::iterator it = blocks_.begin(); it != blocks_.end();) {
		(*it)->Update();

		if ((*it)->GetIsDead()) {
			gameObjectManager_->ClearObj3dData((*it)->INameable::GetName());
			it = blocks_.erase(it); // 削除後、次のイテレーターを取得
		}
		else {
			++it; // 削除しない場合のみインクリメント
		}
	}
}
