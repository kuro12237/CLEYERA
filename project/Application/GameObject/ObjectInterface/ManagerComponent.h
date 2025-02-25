#pragma once

#include "ObjectComponent.h"
#include "Utility/ObjectManager/GameObjectManager.h"
#include "Utility/convert/convert.h"

class GravityManager;

/// <summary>
/// マネージャーリスト抽象クラス
/// </summary>
class ManagerComponent : public JsonComponent
{
 public:
   ManagerComponent() { gameObjectManager_ = GameObjectManager::GetInstance(); };
   virtual ~ManagerComponent() {};

   /// <summary>
   /// 初期化
   /// </summary>
   /// <param name="data"></param>
   virtual void Initialize() = 0;

   /// <summary>
   /// 更新
   /// </summary>
   virtual void Update() = 0;

   /// <summary>
   /// ImGui更新
   /// </summary>
   virtual void ImGuiUpdate() {};

   void ImGuiBegin(string tag) { ImGui::Begin(tag.c_str()); };
   void ImGuiEnd() { ImGui::End(); }

   /// <summary>
   /// 空か確認空だった場合削除
   /// </summary>
   void RemoveEmptyObjList();

   void GravityManagerObjListPush(weak_ptr<GravityManager> g);

#pragma region Set

   void SetGameStartFlag(bool *f) { isGameStartFlag_ = f; }

#pragma endregion

#pragma region Get
   bool *GetIsStartFlag() { return isGameStartFlag_; }
#pragma endregion

 private:
 protected:
   GameObjectManager *gameObjectManager_ = nullptr;
   list<weak_ptr<ObjectComponent>> objDataList_;
   size_t countMax_ = 0;

   bool *isGameStartFlag_ = nullptr;
};