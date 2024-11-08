#include "PlayerStateJamp.h"

void PlayerStateJamp::Initialize(Player* p)
{
	const float jampMax = 0.35f;
	Math::Vector::Vector3 velo = p->GetVelocity();
	velo.y = jampMax;
	p->SetVelocity(velo);
}

void PlayerStateJamp::Update([[maybe_unused]]Player* p)
{

}
