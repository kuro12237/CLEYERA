#pragma once
#include"Sprite/Sprite.h"
#include"GameObject/ObjectInterface/ISpriteData.h"

/// <summary>
/// ���A�C�R���N���X
/// </summary>
class RodingIcon2d :public ISpriteData
{
public:
	RodingIcon2d() {};
	~RodingIcon2d() {};

	void Initialize(uint32_t noiseTex = 0);

	void Update();

	void ImGuiUpdate()override;

#pragma region Set
	void SetP_DissolveMask(const float& mask) { p_dissolveMask_ = &mask; }
#pragma endregion

private:

	const float* p_dissolveMask_ = nullptr;

	float dissolveMaskMax_ = 0.0f;
	Math::Vector::Vector2 edgeMinMax_ = {};
	Math::Vector::Vector4 edgeColor_ = { 1,1,1,1 };

	float rotateSpeed_ = 0.0f;
};