#pragma once
#include"Pch.h"
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"GameObject/UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// UIの抽象クラス
/// </summary>
class ISceneUI
{
public:
	ISceneUI() {globalVariables_ = GlobalVariables::GetInstance();};
	virtual ~ISceneUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 2d表示
	/// </summary>
	void Draw2d();

	void ImGuiUpdate();

private:

protected:

	/// <summary>
	/// uiのデータをspriteに移動
	/// </summary>
	void PushSpriteData();

	/// <summary>
	/// SceneEnumUINoneで作製
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
