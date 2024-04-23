#pragma once
#include"IGravity.h"
#include"WorldTransform.h"

class GameGravityManager
{
public:
	GameGravityManager() {};
	~GameGravityManager() {};

	void PushList(IGravity* g) { objGravitysList_.push_back(g); };

	void CheckAllGravity();

	void ClearList() { objGravitysList_.clear(); }

private:

	const float gravity_ = 0.01f;

	list<IGravity*>objGravitysList_ = {};

};