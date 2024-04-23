#pragma once
#include "Pch.h"
#include"WorldTransform.h"

class Player;
class IGravity
{
public:
	IGravity() {};
	virtual ~IGravity() {};

	void SetVelocity(const Math::Vector::Vector2& v) { velocity_ = &v; }

	Math::Vector::Vector2 GetVelocity() { return *velocity_; }

	void SetWorldTransform(const WorldTransform& w) { worldTransform_ = &w; }

	virtual void GravityExc(const Math::Vector::Vector2 &g) = 0;;

private:

	const Math::Vector::Vector2 *velocity_ = nullptr;
	const WorldTransform* worldTransform_ = nullptr;
};
