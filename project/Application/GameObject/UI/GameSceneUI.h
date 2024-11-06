#pragma once
#include"Sprite/Sprite.h"
#include"ISceneUI.h"

#include"JoyUI/JoyStickUI.h"
#include"JoyUI/JoyStickBackUI.h"

#include"GameSceneBottonUI/BaseBottonUI.h"

#include"GameSceneBottonsAction.h"
#include"GameSceneUIControl.h"

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

	void ImGuiUpdate();


private:

	uint32_t joyStickMax_ = 2;
	vector<JoyStickUIData>joyStickUis_;
	vector<shared_ptr<BaseBottonUI>>bottonUis_;

	unique_ptr<GameSceneUIBottonsAction>bottonAction_ = nullptr;
	unique_ptr<GameSceneUIBottonsControl>bottonControl_ = nullptr;

#ifdef _USE_IMGUI

	string newSpriteName_ = "";

#endif // _USE_IMGUI


};
