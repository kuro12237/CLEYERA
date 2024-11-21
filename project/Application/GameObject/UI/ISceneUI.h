#pragma once
#include"Pch.h"
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"GameObject/UI/BaseSceneBottonUI/BaseBottonUI.h"
#include"Utility/convert/convert.h"
#include"Utility/convert/convert.h"

/// <summary>
/// UI�̒��ۃN���X
/// </summary>
class ISceneUI
{
public:
	ISceneUI() {globalVariables_ = GlobalVariables::GetInstance();};
	virtual ~ISceneUI() {};

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() { BottonUiUpdate(); };

	/// <summary>
	/// 2d�\��
	/// </summary>
	void Draw2d();

	void ImGuiUpdate();

private:

protected:

	/// <summary>
	/// ui�̃f�[�^��sprite�Ɉړ�
	/// </summary>
	void PushSpriteData();

	/// <summary>
	/// SceneEnumUINone�ō쐻
	/// </summary>
	/// <param name="gruopKey"></param>
	void KeyCreateEnumNoneUI(const string & gruopKey);

	/// <summary>
	/// ui�}�b�v�ɃZ�b�g
	/// </summary>
	void PushUiMapData(shared_ptr<BaseBottonUI>ui);

	/// <summary>
	/// bottonUiMap�X�V
	/// </summary>
	void BottonUiUpdate();

	GlobalVariables* globalVariables_ = nullptr;

	map<string,shared_ptr<BaseBottonUI>>bottonUis_;
	map<string,weak_ptr<ISpriteData>>sprites_;

#ifdef _USE_IMGUI

	string newSpriteName_ = "";

#endif // _USE_IMGUI
};
