#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"

class GravityManager
{
public:
	GravityManager() {};
	~GravityManager() {};

	void ClearList() { objectDatas_.clear(); }

	void PushList(IObjectData* data) { objectDatas_.push_back(data); }

	void CheckGravity();

private:

	list<IObjectData*>objectDatas_;

	float gravity_ = 0.01f;

};
