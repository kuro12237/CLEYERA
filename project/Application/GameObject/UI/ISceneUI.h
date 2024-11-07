#pragma once
#include"Pch.h"
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"GameObject/UI/BaseSceneBottonUI/BaseBottonUI.h"

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
	virtual void Update() = 0;

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

	GlobalVariables* globalVariables_ = nullptr;

	vector<shared_ptr<BaseBottonUI>>bottonUis_;
	vector<weak_ptr<ISpriteData>>sprites_;

#ifdef _USE_IMGUI

	string newSpriteName_ = "";

#endif // _USE_IMGUI
};
