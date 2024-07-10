#include "PlayerStateNone.h"

void PlayerStateNone::Initialize(Player* p)
{
	AABB aabb;
	aabb.max = { 1.0f,2.0f,1.0f };
	aabb.min = { -1.0f,-2.0f,-1.0f };
	p->SetAABB(aabb);
}

void PlayerStateNone::Update(Player* p)
{
	p;
}
