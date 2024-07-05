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
				//めり込み計算
				colliderA->ClearExtrusion();
				colliderA->ClearHitDirection();

				CheckExtrusion(colliderA, colliderB);

				colliderA->OnCollision(colliderB);
				colliderB->OnCollision(colliderA);
			}
		}
	}

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

bool BoxCollisionManager::CheckBottomCollsion(float t, ICollider* a, ICollider* b)
{
	a, b;
	Math::Vector::Vector2 RThetaV;
	RThetaV.x = b->GetAABB().max.y;
	RThetaV.y = b->GetAABB().max.x;

	Math::Vector::Vector2 LThetaV;
	LThetaV.x = b->GetAABB().max.y;
	LThetaV.y = b->GetAABB().min.x;

	// atan2 を使用して角度を計算し、度数法に変換
	float RTtheta = std::atan2(RThetaV.x, RThetaV.y) * (180.0f / float(std::numbers::pi)) + 180.0f;
	float LTtheta = std::atan2(LThetaV.x, LThetaV.y) * (180.0f / float(std::numbers::pi)) + 180.0f;

	// t を度数法に変換
	float theta = t * (180.0f / float(std::numbers::pi)) + 180.0f;

	if (theta > RTtheta && theta < LTtheta) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckTopCollision(float t, ICollider* a, ICollider* b)
{

	a, b;
	Math::Vector::Vector2 RBhetaV;
	RBhetaV.x = b->GetAABB().min.y;
	RBhetaV.y = b->GetAABB().max.x;

	Math::Vector::Vector2 LBhetaV;
	LBhetaV.x = b->GetAABB().min.y;
	LBhetaV.y = b->GetAABB().min.x;

	// atan2 を使用して角度を計算し、度数法に変換
	float RBtheta = std::atan2(RBhetaV.x, RBhetaV.y) * (180.0f / float(std::numbers::pi)) + 90.0f;

	float LBtheta = std::atan2(LBhetaV.x, LBhetaV.y) * (180.0f / float(std::numbers::pi)) + 270.0f;
	// t を度数法に変換
	float theta = t * (180.0f / float(std::numbers::pi)) + 180.0f;

	if (theta > RBtheta && theta < LBtheta) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckLeftCollision(float t, ICollider* a, ICollider* b)
{
	a, b,t;
	a, b;
	Math::Vector::Vector2 RThetaV;
	RThetaV.x = b->GetAABB().max.y;
	RThetaV.y = b->GetAABB().max.x;

	Math::Vector::Vector2 RBhetaV;
	RBhetaV.x = b->GetAABB().min.y;
	RBhetaV.y = b->GetAABB().max.x;

	// atan2 を使用して角度を計算し、度数法に変換
	float RTtheta = std::atan2(RThetaV.x, RThetaV.y) * (180.0f / float(std::numbers::pi));
	float LTtheta = std::atan2(RBhetaV.x, RBhetaV.y) * (180.0f / float(std::numbers::pi))+180.0f;

	// t を度数法に変換
	float theta = t * (180.0f / float(std::numbers::pi))+90.0f;

	if (theta > RTtheta && theta < LTtheta) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckRightCollision(float t, ICollider* a, ICollider* b)
{
	a, b, t;
	a, b;
	Math::Vector::Vector2 RThetaV;
	RThetaV.x = b->GetAABB().max.y;
	RThetaV.y = b->GetAABB().min.x;

	Math::Vector::Vector2 RBhetaV;
	RBhetaV.x = b->GetAABB().min.y;
	RBhetaV.y = b->GetAABB().min.x;

	// atan2 を使用して角度を計算し、度数法に変換
	float LTtheta = std::atan2(RThetaV.x, RThetaV.y) * (180.0f / float(std::numbers::pi));//18
	float LBtheta = std::atan2(RBhetaV.x, RBhetaV.y) * (180.0f / float(std::numbers::pi)) + 360.0f;;//36

	// t を度数法に変換
	float theta = t * (180.0f / float(std::numbers::pi));

	if (theta < 0)
	{
		theta += 360.0f;
	}

	if (theta > LTtheta && theta < LBtheta) {
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
	float theta = atan2(a->GetpTransform().translate.y - b->GetpTransform().translate.y, a->GetpTransform().translate.x - b->GetpTransform().translate.x);

	//Aをもとにめり込み度を算出
	Math::Vector::Vector2 extrusionA = {};
	Math::Vector::Vector2 extrusionB = {};

	if (CheckBottomCollsion(theta, a, b))
	{
		//下
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(BOTTOM);
			extrusionA.y = BottomExtrusion(a, b);
		}
		//上
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(TOP);
			extrusionB.y = TopExtrusion(a, b);
		}
	}

	//上
	if (CheckTopCollision(theta,a,b))
	{
		//上
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(TOP);
			extrusionA.y = TopExtrusion(a, b);
		}
		//下
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(BOTTOM);
			extrusionB.y = BottomExtrusion(a, b);
		}
	}

	//左
	if (CheckLeftCollision(theta, a, b))
	{
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(LEFT);
			extrusionA.x = RightExtrusion(a, b);
		}
		//右
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(RIGHT);
			extrusionB.x = LeftExtrusion(a, b);
		}
	}
	//右
	if (CheckRightCollision(theta,a,b))
	{
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(RIGHT);
			extrusionA.x = LeftExtrusion(a, b);
		}
		//左
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(LEFT);
			extrusionB.x = RightExtrusion(a, b);
		}
	}
	a->SetExtrusion(extrusionA);
	b->SetExtrusion(extrusionB);
}

