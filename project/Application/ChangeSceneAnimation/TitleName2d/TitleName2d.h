#pragma once
#include"GameObject/ObjectManager/IObjectData.h"
#include"Sprite/Sprite.h"

class TitleName2d :public IObjectData
{
public:
	TitleName2d() {};
	~TitleName2d() {};

	void Initialize();

	void Update();

	void Draw2d();

private:

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	string filePath_ = "";
	uint32_t texHandle_ = 0;


};