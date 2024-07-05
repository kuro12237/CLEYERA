#pragma once

#include"STransformEular.h"
#include"Pch.h"
#include"Input.h"

#include"Utility/DeltaTimer/DeltaTimer.h"
#include"Utility/ObjectId/GameObjectId.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"


class CollisionTestBox:public IObjectData,public ICollider 
{
public:
	CollisionTestBox() {};
	~CollisionTestBox() {};

	void Initialize();

	void ImGuiUpdate();


	void Update();

	void OnCollision(ICollider* c)override;

private:

};
