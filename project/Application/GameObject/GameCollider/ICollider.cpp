#include "ICollider.h"
#include"GameObject/ObjectManager/IObjectData.h"

void ICollider::ClearAllHitsIds()
{
    while (!allHitIds.empty()) {
        allHitIds.pop();
    }

}
