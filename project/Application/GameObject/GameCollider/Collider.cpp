#include "Collider.h"

void Collider::ClearAllHitsIds()
{
    while (!allHitIds.empty()) {
        allHitIds.pop();
    }

}
