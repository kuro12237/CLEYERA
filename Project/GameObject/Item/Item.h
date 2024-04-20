#pragma once
#include"Game3dObject.h"

class Item
{
public:
	Item() {};
	~Item() {};

	void Initialize();

	void Update();

	void Draw(const CameraData& camera);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_ = {};


	WorldTransform worldTransoform_ = {};

};
