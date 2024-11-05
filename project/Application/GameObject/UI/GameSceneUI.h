#pragma once
#include"Sprite/Sprite.h"
#include"ISceneUI.h"

#include"JoyUI/JoyStickUI.h"
#include"JoyUI/JoyStickBackUI.h"

enum class GameSceneUIEnum
{
	JoyStick_L,
	JoyStick_R,
};

struct JoyStickUIData
{
	shared_ptr<JoyStickUI>stickUi = nullptr;
	shared_ptr<JoyStickBackUI>backUi = nullptr;
};


/// <summary>
/// �Q�[������UI
/// </summary>
class GameSceneUI :public ISceneUI
{
public:
	GameSceneUI() {};
	~GameSceneUI() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// 2d�\��
	/// </summary>
	void Draw2d()override;

private:

	uint32_t joyStickMax_ = 2;
	vector<JoyStickUIData>joyStickUis_;
};
