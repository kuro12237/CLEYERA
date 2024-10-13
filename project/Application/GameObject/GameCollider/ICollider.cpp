#include "ICollider.h"

void ICollider::ClearAllHitsIds()
{
    while (!allHitIds.empty()) {
        allHitIds.pop();
    }

}
