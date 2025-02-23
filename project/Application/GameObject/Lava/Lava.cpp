#include "Lava.h"

void Lava::Initialize()
{
  name_ = "Lava";
  this->SetObjectParamData();

  auto data = objectData_.lock();

  lavaParticle_ = make_shared<LavaParticle>();
  lavaParticle_->SetLavaScale(data->GetWorldTransform().transform.scale);
  lavaParticle_->Initialize();
  lavaParticle_->SetLavaPos(data->GetWorldTransform().transform.translate);
}

void Lava::Update()
{
#ifdef _USE_IMGUI

  lavaParticle_->ImGuiUpdate();

#endif // _USE_IMGUI

  auto &wt = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();
  auto &objParam = gameObjectManager_->GetObj3dData(name_)->GetGameObject();
  auto &objDesc = gameObjectManager_->GetObj3dData(name_)->GetDesc();
  objDesc.colorDesc.uvTranslate.y += 10.0f;
  objParam->SetDesc(objDesc);

  if (p_CameraPos_) {
    wt.transform.translate.z = p_CameraPos_->z;
  }

  lavaParticle_->Update();
}
