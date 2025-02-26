#pragma once

#include "GameObject/ObjectInterface/ObjectComponent.h"
#include "Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// プレイヤーカメラ
/// </summary>
class PlayerCamera : public ObjectComponent
{
 public:
   PlayerCamera() {};
   ~PlayerCamera() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

#pragma region Set

   void SetTarget(const Engine::Transform::WorldTransform &t, string name)
   {
      targetName_ = name;
      target_ = &t;
   }

#pragma endregion

#pragma region Get

#pragma endregion

 private:
   void Shake();

   Math::Vector::Vector3 CalcOffset(const Engine::Transform::WorldTransform &w,
                                    const Math::Vector::Vector3 v) const;
   string targetName_ = "";
   const Engine::Transform::WorldTransform *target_ = nullptr;

   Math::Vector::Vector3 interTarget_{};
   float distructionAngleY_ = 0.0f;

   Math::Vector::Vector2 cameraShakeRadious_ = {-1.0f, 1.0f};
   bool isShake_ = false;

   float cameraFacter_ = 0.0f;
   Math::Vector::Vector3 cameraOffset_ = {};

   float cameraRotateX_ = 0.0f;
};
