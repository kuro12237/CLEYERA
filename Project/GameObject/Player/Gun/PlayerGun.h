#pragma once
#include"GameObject/ObjectManager/IObjectData.h"

class PlayerGun:public IObjectData
{
public:
	PlayerGun() {};
	~PlayerGun() {};

	void Initialize();

	void Update();

private:

};