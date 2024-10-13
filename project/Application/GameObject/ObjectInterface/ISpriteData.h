#pragma once
#include"GameObject/ObjectManager/IObjectData.h"
#include"Sprite/Sprite.h"

class ISpriteData
{
public:
	ISpriteData() {};
	~ISpriteData() {};

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw2d() = 0;

private:

protected:

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	string filePath_ = "";
	uint32_t texHandle_ = 0;

};
