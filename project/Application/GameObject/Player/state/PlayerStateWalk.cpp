#include "PlayerStateWalk.h"

void PlayerStateWalk::Initialize([[maybe_unused]] Player* p)
{

}

void PlayerStateWalk::Update([[maybe_unused]] Player* p)
{
	auto& rotate = GameObjectManager::GetInstance()->GetObj3dData(p->INameable::GetName())->GetWorldTransform().transform.rotate;

	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();

	float joystickThreshold_ = 0.2f;
	if (std::abs(Ljoy.x) > joystickThreshold_ || std::abs(Ljoy.y) > joystickThreshold_)
	{
		p->MarkStateForRemoval<PlayerStateWalk>();
	}

	p->WalkanimationAddFlame((1.0f / 30.0f) * fabsf(Ljoy.x));

	Math::Vector::Vector3 velo = p->GetVelocity();
	velo.x = Ljoy.x * 0.2f;
	p->SetVelocity(velo);

	//âE
	const float degrees = 90.0f;
	float radian = 0.0f;
	if (velo.x > 0.0f)
	{
		radian = Math::Vector::degreesToRadians(degrees);
	}
	//ç∂
	if (velo.x < 0.0f)
	{
		radian = Math::Vector::degreesToRadians(-degrees);
	}

	rotate.y = radian;


}

