#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"Input.h"

class Player :public IObjectData
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

private:
	
};
