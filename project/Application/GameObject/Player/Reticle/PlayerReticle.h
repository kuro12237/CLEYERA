#pragma once
#include"WorldTransform.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Input.h"
#include"Sprite/Sprite.h"
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// レティクルクラス
/// </summary>
class PlayerReticle :public IObjectData
{
public:
	PlayerReticle() {};
	~PlayerReticle() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ImGui更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 2d描画
	/// </summary>
	void Draw2d();

#pragma region command

	void Move();

#pragma endregion

private:

	Math::Vector::Vector3 NDCToScreen(const Math::Vector::Vector3& ndc, float screenWidth, float screenHeight);

	float rethickeAngle_ = 0.0f;
	const float kRetickeRad_ = 3.0f;
	Math::Vector::Vector2 reticlePos_ = {kRetickeRad_,0.0f};

	Math::Vector::Vector2 pos2d_ = {};

	unique_ptr<Engine::Objects::Sprite>sprite_ = nullptr;
	Engine::Transform::WorldTransform worldTransform_;
	Math::Vector::Vector3 interTarget_ = {};
};

