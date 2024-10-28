#pragma once
#include"Sprite/Sprite.h"
#include"UI/GameOverUI.h"
#include"Input/Input.h"
#include"UIActiveParticle/GameOverActiveUIParticle.h"

enum GameOverSelectScene
{
	TITLE,
	GAME,
	SELECT
};

/// <summary>
/// ゲームオーバーのUIクラス
/// </summary>
class GameOverUIManager
{
public:
	GameOverUIManager() {};
	~GameOverUIManager() {};

	void Initialize();

	void Update();

	void Draw2d();

#pragma region Get

	uint32_t GetSelectIndex() { return selectIndex_; }
	bool GetIsSelect() { return isSelect_; }
#pragma endregion


private:

	bool IsLJoystickActive();

	bool isControl = false;
	bool isSelect_ = false;

	int32_t selectIndex_ = 1;
	int32_t selectIndexMin_ = 0;
	int32_t selectIndexMax_ = 2;

	static const int32_t uiMax_ = 3;
	array<unique_ptr<GameOverUI>, uiMax_>gameOverUIs_;

	unique_ptr<Engine::Objects::Sprite>uiBackSprite_ = nullptr;
	array<const Engine::Transform::WorldTransform*,uiMax_>uiBackWorldTransform_{};
	uint32_t uiBackTexhandle_ = 0;

	Math::Vector::Vector2 uiPos_ = {};

	Math::Vector::Vector3 defaultScale_ = { 0.25f,0.25f,0.25f };
	Math::Vector::Vector3 selectScale_ = { 0.35f,0.35f,0.35f };

	float flame_ = 0.0f;
	float flameMax_ = 1.0f;

	unique_ptr<GameOverActiveUIParticle>gameOverActiveparticle_ = nullptr;

};
