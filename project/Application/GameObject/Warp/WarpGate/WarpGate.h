#pragma once

#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"
#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectId/GameObjectId.h"


/// <summary>
/// ワープゲートクラス
/// </summary>
class WarpGate :public IObjectData,public ICollider
{
public:
	WarpGate() {};
	~WarpGate() {};

	void Initialize(const int& index);

	void Update();

	void OnCollision(ICollider* c)override;

#pragma region Get

	const string &GetRailDataFilePath() { return railDataFileName_; }

#pragma endregion


private:

	string railDataFileName_ = "";


};
