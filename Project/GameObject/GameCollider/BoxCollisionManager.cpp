#include "BoxCollisionManager.h"

void BoxCollisionManager::ListClear()
{
	colliders_.clear();
}

void BoxCollisionManager::ListPushback(ICollider* c)
{
	colliders_.push_back(c);
}

void BoxCollisionManager::CheckAllCollisoin()
{
	list<ICollider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		ICollider* colliderA = *itrA;
		list<ICollider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			ICollider* colliderB = *itrB;

			AABB a = SettingAABBParam(colliderA);
			AABB b = SettingAABBParam(colliderB);

			if (colliderA->GetId() == colliderB->GetId())
			{
				continue;
			}

			if (IsCollision(a, b))
			{
				//‚ß‚èž‚ÝŒvŽZ
				colliderA->ClearExtrusion();
				colliderA->ClearHitDirection();

				CheckExtrusion(colliderA, colliderB);

				colliderA->OnCollision(colliderB);
				colliderB->OnCollision(colliderA);
			}
		}
	}

}

float BoxCollisionManager::CalculateAngle(float x, float y)
{
	float angle = std::acosf(x / std::sqrt(x * x + y * y)) * (180.0f / static_cast<float>(std::numbers::pi));
	if (x < 0) {
		angle = 360.0f - angle;
	}
	return NomalizeDegree(angle);
}

float BoxCollisionManager::NomalizeDegree(float theta)
{
	while (theta < 0.0f) {
		theta += 360.0f;
	}
	while (theta >= 360.0f) {
		theta -= 360.0f;
	}
	return theta;
}

AABB BoxCollisionManager::SettingAABBParam(ICollider* c)
{
	AABB result{};
	result.min = {

		.x = c->GetpTransform().translate.x + (c->GetAABB().min.x),
		.y = c->GetpTransform().translate.y + (c->GetAABB().min.y),
		.z = c->GetpTransform().translate.z + (c->GetAABB().min.z),
	};
	result.max = {
		.x = c->GetpTransform().translate.x + (c->GetAABB().max.x),
		.y = c->GetpTransform().translate.y + (c->GetAABB().max.y),
		.z = c->GetpTransform().translate.z + (c->GetAABB().max.z),
	};

	return result;
}
bool BoxCollisionManager::IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckBottomCollsion(float t, Math::Vector::Vector4 bDegree)
{
	float RTtheta = bDegree.x;
	float LTtheta = bDegree.z;

	if (t >= RTtheta+1.0f && t <= LTtheta-1.0f) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckTopCollision(float t, Math::Vector::Vector4 bDegree)
{
	float RBtheta = bDegree.y;
	float LBtheta = bDegree.w;

	if (t < RBtheta && t > LBtheta) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckLeftCollision(float t, Math::Vector::Vector4 bDegree)
{
	float RTtheta = bDegree.x;
	float RBtheta = bDegree.y;

	if (t < RTtheta || t > RBtheta) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckRightCollision(float t, Math::Vector::Vector4 bDegree)
{
	float LTtheta = bDegree.z;
	float LBtheta = bDegree.w;

	if (t > LTtheta && t < LBtheta) {
		return true;
	}
	return false;
}

float BoxCollisionManager::BottomExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().min.y + b->GetAABB().max.y) - (a->GetpTransform().translate.y - b->GetpTransform().translate.y);
}

float BoxCollisionManager::TopExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().max.y + b->GetAABB().min.y) - (a->GetpTransform().translate.y - b->GetpTransform().translate.y);
}

float BoxCollisionManager::RightExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().min.x + b->GetAABB().max.x) - (a->GetpTransform().translate.x - b->GetpTransform().translate.x);
}

float BoxCollisionManager::LeftExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().max.x + b->GetAABB().min.x) - (a->GetpTransform().translate.x - b->GetpTransform().translate.x);
}

void BoxCollisionManager::CheckExtrusion(ICollider* a, ICollider* b)
{
	//A‚ð‚à‚Æ‚É‚ß‚èž‚Ý“x‚ðŽZo
	Math::Vector::Vector2 extrusionA = {};
	Math::Vector::Vector2 extrusionB = {};

	//b‚Ì‘ÎŠpü‚ÌŠp“xŽZo
	//xRT/yRB/zLT/wLB
	Math::Vector::Vector4 vertexDegrees = {
		std::atan2(b->GetAABB().max.y, b->GetAABB().max.x)* (180.0f / float(std::numbers::pi)),
		std::atan2(b->GetAABB().min.y, b->GetAABB().max.x)* (180.0f / float(std::numbers::pi)),
		std::atan2(b->GetAABB().max.y, b->GetAABB().min.x)* (180.0f / float(std::numbers::pi)),
		std::atan2(b->GetAABB().min.y, b->GetAABB().min.x)* (180.0f / float(std::numbers::pi))
	};

	vertexDegrees.x = NomalizeDegree(vertexDegrees.x);
	vertexDegrees.y = NomalizeDegree(vertexDegrees.y);
	vertexDegrees.z = NomalizeDegree(vertexDegrees.z);
	vertexDegrees.w = NomalizeDegree(vertexDegrees.w);

	float theta =atan2(a->GetpTransform().translate.y - b->GetpTransform().translate.y, a->GetpTransform().translate.x - b->GetpTransform().translate.x);
	theta = theta * (180.0f / float(std::numbers::pi));
	theta = NomalizeDegree(theta);

	if (CheckBottomCollsion(theta, vertexDegrees))
	{
		//‰º
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(BOTTOM);
			extrusionA.y = BottomExtrusion(a, b);
		}
		//ã
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(TOP);
			extrusionB.y = TopExtrusion(a, b);
		}
	}//ã

	if (CheckTopCollision(theta, vertexDegrees))
	{
		//ã
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(TOP);
			extrusionA.y = TopExtrusion(a, b);
		}
		//‰º
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(BOTTOM);
			extrusionB.y = BottomExtrusion(a, b);
		}
	}

	//¶
	if (CheckLeftCollision(theta, vertexDegrees))
	{
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(LEFT);
			extrusionA.x = RightExtrusion(a, b);
		}
		//‰E
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(RIGHT);
			extrusionB.x = LeftExtrusion(a, b);
		}
	}
	//‰E
	if (CheckRightCollision(theta, vertexDegrees))
	{
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(RIGHT);
			extrusionA.x = LeftExtrusion(a, b);
		}
		//¶
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(LEFT);
			extrusionB.x = RightExtrusion(a, b);
		}
	}
	a->SetExtrusion(extrusionA);
	b->SetExtrusion(extrusionB);
}

