#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"

class Player :public IObjectData,public ICollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();


	void OnCollision(ICollider* c)override;

private:

};
