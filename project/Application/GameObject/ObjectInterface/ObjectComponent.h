#pragma once
#include "Utility/GlobalVariables/GlobalVariables.h"
#include "Utility/ObjectManager/GameObjectManager.h"
#include "WorldTransform.h"

#include "JsonComponent.h"

#include "../GameCollider/Collider.h"
#include "INameable.h"

class GameObjectManager;

class Collider;
/// <summary>
/// オブジェクトの抽象クラス
/// </summary>
class ObjectComponent : public INameable, public JsonComponent
{
 public:
   ObjectComponent();
   virtual ~ObjectComponent() {};

   void CalcGravity(float g);

   /// <summary>
   /// objectのデータをコライダーにセット
   /// </summary>
   void SetColliderParamData();

   virtual void OnCollision([[maybe_unused]] ObjectComponent *objectData) {};

   void SetObjectParamData();

   virtual void Initialize() = 0;

   virtual void Update() = 0;

#pragma region Set
   void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }
   void SetIsUseGravityFlag(bool f) { isUseGravityFlag_ = f; }
#pragma endregion

#pragma region Get
   Math::Vector::Vector3 GetVelocity() { return velocity_; }
   Collider *GetCollider() { return collider_.get(); }
   weak_ptr<IGameObjectData> GetObjectData() { return objectData_; }

   bool GetIsUseGravityFlag() { return isUseGravityFlag_; }
#pragma endregion

 private:
 protected:
   bool isUseGravityFlag_ = true;

   Math::Vector::Vector3 velocity_{};

   unique_ptr<Collider> collider_ = nullptr;

   weak_ptr<IGameObjectData> objectData_;

   GameObjectManager *gameObjectManager_ = nullptr;
};
