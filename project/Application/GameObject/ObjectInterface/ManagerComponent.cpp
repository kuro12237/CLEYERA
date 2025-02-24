#include "ManagerComponent.h"
#include "GameObject/GravityManager/GravityManager.h"

void ManagerComponent::RemoveEmptyObjList()
{
   objDataList_.erase(
       std::remove_if(objDataList_.begin(), objDataList_.end(),
                      [](const std::weak_ptr<ObjectComponent> &obj) { return obj.expired(); }),
       objDataList_.end());
}

void ManagerComponent::GravityManagerObjListPush(weak_ptr<GravityManager> g)
{
   auto gravityManager = g.lock();

   for (weak_ptr<ObjectComponent> obj : objDataList_) {
      auto it = obj.lock();

      if (it) {
         if (it->GetIsUseGravityFlag()) {
            gravityManager->PushList(it.get());
         }
      }
   }
}
