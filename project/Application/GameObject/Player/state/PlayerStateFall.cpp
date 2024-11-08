#include "PlayerStateFall.h"

void PlayerStateFall::Initialize([[maybe_unused]]Player* p)
{
}

void PlayerStateFall::Update([[maybe_unused]] Player* p)
{
	if (p->GetVelocity().y>=0.0f)
	{
		p->MarkStateForRemoval<PlayerStateFall>();
	}
}
