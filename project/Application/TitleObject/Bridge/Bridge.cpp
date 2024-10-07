#include "Bridge.h"

void Bridge::Initialize()
{
	name_ = "Bridge";
	gameObjectManager_ = GameObjectManager::GetInstance();
}

void Bridge::Update()
{
	auto& wt = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();

	if (isStartAnimation_)
	{
		startPos_ = targetPos_;
		startPos_.y = -4.0f;
		wt.transform.translate.z = targetPos_.z;

		isStartAnimation_ = false;
		isAnimation_ = true;
	}

	if (isAnimation_)
	{
		if (animationFlame_ <= animationFlameMax_)
		{
			//•âŠÔ
			animationFlame_ += animationFlameSpeed_;
			wt.transform.translate.y = Math::Vector::Lerp(startPos_.y, targetPos_.y, this->EaseOutBounce(animationFlame_));
			//”’l‚Ì•â³
			if (wt.transform.translate.y >= 0.0f)
			{
				wt.transform.translate.y = 0.0f;
			}
		}
		else
		{
			animationFlame_ = 0.0f;
			isAnimation_ = false;
		}
	}
}

float Bridge::EaseOutBounce(float x)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1.0f / d1) {
		return n1 * x * x;
	}
	else if (x < 2.0f / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

Math::Vector::Vector3  Bridge::EaseOutBounceLerp(const Math::Vector::Vector3& startPos, const Math::Vector::Vector3& endPos, float t)
{
	float bounceT = EaseOutBounce(t);
	return Math::Vector::Lerp(startPos, endPos, bounceT);
}