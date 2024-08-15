#include "GravityManager.h"

void GravityManager::CheckGravity()
{
	list<IObjectData*>::iterator itrA = objectDatas_.begin();

	for (; itrA != objectDatas_.end(); ++itrA) {

		IObjectData* objA = *itrA;
		objA->CalcGravity(-gravity_);
	}
}
