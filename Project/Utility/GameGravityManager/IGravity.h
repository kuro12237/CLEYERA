#pragma once
#include"VectorTransform.h"
#include"WorldTransform.h"

class Player;
class IGravity
{
public:
	IGravity() {};
	virtual ~IGravity() {};

	void SetVelocity(const Vector2& v) { velocity_ = &v; }

	Vector2 GetVelocity() { return *velocity_; }

	void SetWorldTransform(const WorldTransform& w) { worldTransform_ = &w; }

	virtual void GravityExc(const Vector2 &g) = 0;;

private:

	const Vector2 *velocity_ = nullptr;
	const WorldTransform* worldTransform_ = nullptr;
};
