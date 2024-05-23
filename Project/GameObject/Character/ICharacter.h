#pragma once
#include"CameraData.h"
#include"WorldTransform.h"
#include"Game3dObject.h"
#include"Utility/CollisionManager/Collider/OBBCollider.h"

class ICharacter
{
public:
	ICharacter() {};
	virtual ~ICharacter() {};

	virtual void Initilaize();

	void Draw(const CameraData& camera,const WorldTransform& wt);

	virtual void OnCollision(uint32_t id);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;


};
