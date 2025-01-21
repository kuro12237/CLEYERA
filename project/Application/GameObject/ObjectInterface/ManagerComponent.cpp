#include "ManagerComponent.h"

void ManagerComponent::RemoveEmptyObjList()
{
    objDataList_.erase(
        std::remove_if(objDataList_.begin(), objDataList_.end(),
            [](const std::weak_ptr<IObjectData>& obj) {
                return obj.expired();
            }),
        objDataList_.end());
}
