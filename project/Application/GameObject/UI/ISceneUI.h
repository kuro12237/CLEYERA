#pragma once
#include "GameObject/ObjectInterface/ISpriteData.h"
#include "GameObject/UI/BaseSceneBottonUI/BaseBottonUI.h"
#include "Pch.h"
#include "Utility/convert/convert.h"

/// <summary>
/// UIの抽象クラス
/// </summary>
class ISceneUI
{
public:
  ISceneUI() { globalVariables_ = GlobalVariables::GetInstance(); };
  virtual ~ISceneUI() {};

  /// <summary>
  /// 初期化
  /// </summary>
  virtual void Initialize() = 0;

  /// <summary>
  /// 更新
  /// </summary>
  virtual void Update() { BottonUiUpdate(); };

  /// <summary>
  /// 2d表示
  /// </summary>
  void Draw2d();

  /// <summary>
  /// パーティクルの表示
  /// </summary>
  virtual void ParticleDraw2d() {};

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
  void KeyCreateEnumNoneUI(const string &gruopKey);

  /// <summary>
  /// uiマップにセット
  /// </summary>
  void PushUiMapData(shared_ptr<BaseBottonUI> ui);

  /// <summary>
  /// bottonUiMap更新
  /// </summary>
  void BottonUiUpdate();

  GlobalVariables *globalVariables_ = nullptr;

  map<string, shared_ptr<BaseBottonUI>> bottonUis_;
  map<string, weak_ptr<ISpriteData>> sprites_;

#ifdef _USE_IMGUI

  string newSpriteName_ = "";

#endif // _USE_IMGUI
};
