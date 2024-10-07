#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"

class TitleCamera :public IObjectData
{
public:
	TitleCamera() {};
	~TitleCamera() {};

	void Initialize();

	void Update();

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	float speed_ = 0.1f;

};
