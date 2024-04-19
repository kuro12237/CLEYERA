#include "GameGravityManager.h"

void GameGravityManager::CheckAllGravity()
{
	list<IGravity*>::iterator itrA = objGravitysList_.begin();

	for (; itrA != objGravitysList_.end(); ++itrA) {

		IGravity* g = *itrA;
		Vector2 v = {g->GetVelocity().x, g->GetVelocity().y - gravity_ };

		g->GravityExc(v);

	}
}
