#include "ItemManager.h"

void ItemManager::Initialize()
{
	shared_ptr<Item>item = make_shared<Item>();
	item->Initialize();

	items_.push_back(item);

}

void ItemManager::Update()
{
	items_.remove_if([](shared_ptr<Item>item)
		{
			if (item->GetIsDeadFlag())
			{
				item.reset();
				return true;
			}
			return false;
		});

	for (shared_ptr<Item> item : items_)
	{
		if (item)
		{
			item->Update();
		}
	}
}

void ItemManager::Animation()
{
	for (shared_ptr<Item> item : items_)
	{
		if (item)
		{
			item->Animation();
		}
	}
}

void ItemManager::Draw()
{
	for (shared_ptr<Item> item : items_)
	{
		if (item)
		{
			item->Draw();
		}
	}
}
