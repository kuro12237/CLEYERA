#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// �W���C�X�e�B�b�N2d�\���N���X
/// </summary>
class ClearSceneTitleText
{
public:
	ClearSceneTitleText() {};
	~ClearSceneTitleText() {};

	void Update(BaseBottonUI& ui);

#pragma region Get

#pragma endregion

	void SetisSelect(bool f) { isSelect_ = f; }

private:

	bool isSelect_ = false;
	float flame_ = 0.0f;
};

