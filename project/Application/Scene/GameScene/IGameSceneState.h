#pragma once


class GameScene;
/// <summary>
/// sceneのステート
/// </summary>
class IGameSceneState
{
 public:
   IGameSceneState() {};
   virtual ~IGameSceneState() {};

   virtual void Initialize(GameScene *scene) = 0;
   virtual void Update(GameScene *scene) = 0;
   virtual void ImGuiUpdate() {};
   virtual void Draw2d() {};
};