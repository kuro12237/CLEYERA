#include "PlayerStateSquat.h"

void PlayerStateSquat::Initialize(Player* p)
{
	AABB aabb;
	aabb.max = { 1.0f,0.1f,1.0f };
	aabb.min = { -1.0f,-2.0f,-1.0f };
	p->SetAABB(aabb);
}

void PlayerStateSquat::Update(Player* p)
{
	p;
}
