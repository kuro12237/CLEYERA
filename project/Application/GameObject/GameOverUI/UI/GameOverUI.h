#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"


/// <summary>
/// ゲームオーバーのUI
/// </summary>
class GameOverUI :public ISpriteData
{
public:
	GameOverUI() {};
	~GameOverUI() {};


	void Initialize();

	void ImGuiUpdate()override;

	void Update();

#pragma region Set
	void SetSelectIndex(const uint32_t& index) { selectIndex_ = index; }
	void SetTranslate(const Math::Vector::Vector3& translate) { worldTransform_.transform.translate = translate; }
	void SetScale(const Math::Vector::Vector3& scale) { worldTransform_.transform.scale = scale; }
#pragma endregion

#pragma region Get

	Math::Vector::Vector2 GetTexSize() { return texSize_; }
#pragma endregion

private:

	uint32_t selectIndex_ = 0;

	Math::Vector::Vector3 scale_ = { 0.25f,0.25f,0.25f };
	Math::Vector::Vector2 texSize_ = { 0.0f,0.0f };
};
