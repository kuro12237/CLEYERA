#pragma once
#include"WorldTransform.h"
#include"GameObject/ObjectManager/GameObjectManager.h"
#include"Input.h"
#include"Sprite/Sprite.h"

class PlayerReticle :public IObjectData
{
public:
	PlayerReticle() {};
	~PlayerReticle() {};

	void Initialize();

	void ImGuiUpdate();

	void Update();

	void Draw2d();

#pragma region command

	void Move();

#pragma endregion

private:

	Math::Vector::Vector3 NDCToScreen(const Math::Vector::Vector3& ndc, float screenWidth, float screenHeight);

	float rethickeAngle_ = 0.0f;
	const float kRetickeRad_ = 4.0f;
	Math::Vector::Vector2 reticlePos_ = {kRetickeRad_,0.0f};

	Math::Vector::Vector2 pos2d_ = {};

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_;
};

