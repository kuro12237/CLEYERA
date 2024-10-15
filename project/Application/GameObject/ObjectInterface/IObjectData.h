#pragma once
#include"WorldTransform.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

class GameObjectManager;

/// <summary>
/// オブジェクトの抽象クラス
/// </summary>
class IObjectData
{
public:
	IObjectData();
	virtual ~IObjectData() {};

	void CalcGravity(float g);

	void CreateJsonData();

	template<typename T>
	void AddJsonItem(string itemName, T value) { return globalVariables_->AddItem(name_, itemName, value); }

	template<typename T>
	T GetJsonItem(string itemName) { return globalVariables_->GetValue<T>(name_, itemName); }

#pragma region Set
	void SetName(string name) { name_ = name; }
	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }
#pragma endregion

#pragma region Get
	string GetName() { return name_; }
	Math::Vector::Vector3 GetVelocity() { return velocity_; }
#pragma endregion

private:

protected:

	string name_ = "";
	Math::Vector::Vector3 velocity_{};

	GlobalVariables* globalVariables_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;

};

