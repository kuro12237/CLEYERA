#pragma once
#include"Item.h"

class ItemManager
{
public:
	ItemManager() {};
	~ItemManager() {};

	void Initialize();

	void Update();

	void Animation();

	void Draw();

#pragma region Get

	list<shared_ptr<Item>>GetItems() { return items_; };


#pragma endregion

private:

	list<shared_ptr<Item>>items_{};


};