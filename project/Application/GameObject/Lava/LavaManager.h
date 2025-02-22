#pragma once
#include "GameObject/Lava/Lava.h"
#include "GameObject/ObjectInterface/JsonComponent.h"
#include "GameObject/ObjectInterface/ManagerComponent.h"

/// <summary>
/// Lava管理クラス
/// </summary>
class LavaManager : public ManagerComponent
{
public:
  LavaManager() {};
  ~LavaManager() {};

  void Initialize() override;
  void Update() override;

#pragma region Get

  weak_ptr<Lava> GetLava(size_t index) { return lavas_[index]; }

#pragma endregion

private:
  vector<shared_ptr<Lava>> lavas_;
};