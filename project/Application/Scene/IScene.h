#pragma once
#include"PostEffect/PostEffect.h"
#include "Pch.h"
#include "Utility/ObjectManager/GameObjectManager.h"

#include "GameObject/ObjectInterface/ObjectComponent.h"
#include "GameObject/ObjectInterface/ParticleComponent.h"
#include "GameObject/ObjectInterface/LightComponent.h"
#include "GameObject/ObjectInterface/ManagerComponent.h"

class GameManager;

/// <summary>
/// シーンインターフェース
/// </summary>
class IScene
{
 public:
   IScene()
   {
      postEffect_ = Engine::PostEffect::GetInstance(),
      gameObjectManager_ = GameObjectManager::GetInstance();
   };

   virtual ~IScene() {};

   virtual void Initialize(GameManager *state) = 0;
   virtual void ImGuiUpdate() {};
   virtual void Update(GameManager *state) = 0;
   virtual void PostProcessDraw() {};
   virtual void Back2dSpriteDraw() {};
   virtual void Object3dDraw() {};
   virtual void Flont2dSpriteDraw() {};

 protected:
   void ListInitialize();
   void ListUpdate();

   Engine::PostEffect *postEffect_ = nullptr;
   GameObjectManager *gameObjectManager_ = nullptr;

   list<weak_ptr<ManagerComponent>> managerList_;
   list<weak_ptr<ParticleComponent>> particleList_;
   list<weak_ptr<ObjectComponent>> objctDataList_;
   list<weak_ptr<LightComponent>> lightDataList_;

 private:
};
