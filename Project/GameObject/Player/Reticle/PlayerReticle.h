#pragma once
#include"WorldTransform.h"
#include"GameObject/ObjectManager/GameObjectManager.h"
#include"Input.h"

class PlayerReticle:public IObjectData
{
public:
	PlayerReticle() {};
	~PlayerReticle() {};

	void Initialize();

	void ImGuiUpdate();

	void Update();

#pragma region command

	void Move();

#pragma endregion

private:

	float rethickeAngle_ = 0.0f;
	const float kRetickeRad_ = 4.0f;
	const float kAngleSpeed_ = 1.0f;

};

