#pragma once
#include"Sprite/Sprite.h"
#include"ISceneUI.h"

#include"JoyUI/JoyStickUI.h"
#include"JoyUI/JoyStickBackUI.h"


struct JoyStickUIData
{
	string groupName = "";
	shared_ptr<JoyStickUI>stickUi = nullptr;
	shared_ptr<JoyStickBackUI>backUi = nullptr;
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="direction"></param>
	void Initialize(const JoyStickLeftRight& direction);
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
