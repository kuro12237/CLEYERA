#include "PlayerStateAim.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateAim::Initialize(Player* p)
{
	p;
}

void PlayerStateAim::Update(Player* p)
{
	const float speed =0.05f;
	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();
	Math::Vector::Vector3 velo = p->GetVelocity();

	velo.x = Ljoy.x * speed;
	p->SetVelocity(velo);

	if (p->IsInState<PlayerStateDeadAnimation>())
	{
		p->MarkStateForRemoval<PlayerStateAim>();
		return;
	}
}

