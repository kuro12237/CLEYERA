#include "LavaManager.h"

void LavaManager::Initialize()
{
	this->jsonGropName_ = "LavaManager";
	this->CreateJsonData();

	countMax_ = 1;
	//this->AddJsonItem("LavaMax",countMax_);
	//this->GetJsonItem<int32_t>("LavaMax");

	for (int32_t count = 0; count < this->countMax_; count++)
	{
		shared_ptr<Lava> lava = make_shared<Lava>();
		lavas_.push_back(lava);
		this->objDataList_.push_back(lava);
	}

	for (auto obj : objDataList_)
	{
		obj.lock()->Initialize();
	}
}

void LavaManager::Update()
{
	for (auto obj : objDataList_)
	{
		obj.lock()->Update();
	}
}
