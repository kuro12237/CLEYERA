#include "BoxCollisionManager.h"

void BoxCollisionManager::CollidersAllHitsIdsClear()
{
	datas_.clear();
}

void BoxCollisionManager::ListClear()
{
	datas_.clear();
}

void BoxCollisionManager::End()
{
	ListClear();
	CollidersAllHitsIdsClear();
}

void BoxCollisionManager::ListPushback(ObjectComponent* data)
{
	datas_.push_back(data);
}

void BoxCollisionManager::CheckAllCollisoin()
{
	for (auto itr1 = datas_.begin(); itr1 != datas_.end(); ++itr1) {
		for (auto itr2 = std::next(itr1); itr2 != datas_.end(); ++itr2) {

			// コリジョンフィルタリング
			if (((*itr1)->GetCollider()->GetCollosionAttribute() && (*itr2)->GetCollider()->GetCollisionMask()) == 0 ||
				((*itr1)->GetCollider()->GetCollisionMask() && (*itr2)->GetCollider()->GetCollosionAttribute()) == 0)
			{
				continue;
			}

			AABB a = SettingAABBParam((*itr1)->GetCollider());
			AABB b = SettingAABBParam((*itr2)->GetCollider());

			// 衝突判定をとる
			if (IsCollision(a, b)) 
			{
				//めり込み計算
				(*itr1)->GetCollider()->ClearExtrusion();
				(*itr1)->GetCollider()->ClearHitDirection();

				CheckExtrusion((*itr1)->GetCollider(), (*itr2)->GetCollider());

				(*itr1)->GetCollider()->OnCollision((*itr2));
				(*itr1)->GetCollider()->PushAllHitsIds((*itr2)->GetCollider()->GetId());

				(*itr2)->GetCollider()->OnCollision((*itr1));
				(*itr2)->GetCollider()->PushAllHitsIds((*itr1)->GetCollider()->GetId());

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

AABB BoxCollisionManager::SettingAABBParam(Collider* c)
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

	if (t >= RTtheta && t <= LTtheta) {
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

float BoxCollisionManager::BottomExtrusion(Collider* a, Collider* b)
{
	return (-a->GetAABB().min.y + b->GetAABB().max.y) - (a->GetpTransform().translate.y - b->GetpTransform().translate.y);
}

float BoxCollisionManager::TopExtrusion(Collider* a, Collider* b)
{
	return (-a->GetAABB().max.y + b->GetAABB().min.y) - (a->GetpTransform().translate.y - b->GetpTransform().translate.y);
}

float BoxCollisionManager::RightExtrusion(Collider* a, Collider* b)
{
	return (-a->GetAABB().min.x + b->GetAABB().max.x) - (a->GetpTransform().translate.x - b->GetpTransform().translate.x);
}

float BoxCollisionManager::LeftExtrusion(Collider* a, Collider* b)
{
	return (-a->GetAABB().max.x + b->GetAABB().min.x) - (a->GetpTransform().translate.x - b->GetpTransform().translate.x);
}

void BoxCollisionManager::CheckExtrusion(Collider* a, Collider* b)
{
	//Aをもとにめり込み度を算出
	Math::Vector::Vector2 extrusionA = {};
	Math::Vector::Vector2 extrusionB = {};

	//bの対角線の角度算出
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
	}//上

	if (CheckTopCollision(theta, vertexDegrees))
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
	if (CheckLeftCollision(theta, vertexDegrees))
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
	if (CheckRightCollision(theta, vertexDegrees))
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

