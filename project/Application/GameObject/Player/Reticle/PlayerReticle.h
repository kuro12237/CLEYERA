#pragma once
#include"WorldTransform.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Input.h"
#include"Sprite/Sprite.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"../Player.h"

class Player;

/// <summary>
/// レティクルクラス
/// </summary>
class PlayerReticle :public ObjectComponent
{
public:
	PlayerReticle() {};
	~PlayerReticle() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// ImGui更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 2d描画
	/// </summary>
	void Draw2d();

#pragma region command

	void Move();

#pragma endregion

#pragma region Set
	void SetPlayer(shared_ptr<Player> p) { player_ = p; }
#pragma endregion

private:

	weak_ptr<Player>player_;

	Math::Vector::Vector3 NDCToScreen(const Math::Vector::Vector3& ndc, float screenWidth, float screenHeight);

	float rethickeAngle_ = 0.0f;
	const float kRetickeRad_ = 6.0f;
	Math::Vector::Vector2 reticlePos_ = { kRetickeRad_,0.0f };

	Math::Vector::Vector2 pos2d_ = {};

	unique_ptr<Engine::Objects::Sprite>sprite_ = nullptr;
	Engine::Transform::WorldTransform worldTransform_;
	Math::Vector::Vector3 interTarget_ = {};

	float lerpFlame_ = 0.5f;
};

