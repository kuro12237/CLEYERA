#pragma once
#include"WorldTransform.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"
#include"IJsonHandler.h"
#include"INameable.h"


class GameObjectManager;

/// <summary>
/// オブジェクトの抽象クラス
/// </summary>
class IObjectData:public INameable,public IJsonHandler
{
public:
	IObjectData();
	virtual ~IObjectData() {};

	void CalcGravity(float g);

#pragma region Set
	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }
#pragma endregion

#pragma region Get
	Math::Vector::Vector3 GetVelocity() { return velocity_; }
#pragma endregion

private:

protected:

	Math::Vector::Vector3 velocity_{};

	GameObjectManager* gameObjectManager_ = nullptr;

};

