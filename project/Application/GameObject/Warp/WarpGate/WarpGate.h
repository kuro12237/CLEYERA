#pragma once

#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"
#include"Utility/ObjectId/GameObjectId.h"


/// <summary>
/// ワープゲートクラス
/// </summary>
class WarpGate :public ObjectComponent
{
public:
	WarpGate() {};
	~WarpGate() {};

	void Initialize()override;

	void Update()override;

	void OnCollision(ObjectComponent* objData)override;

#pragma region Get

	const string &GetRailDataFilePath() { return railDataFileName_; }

#pragma endregion

#pragma region Set
	void SetIndex(const int& index) { index_ = index; }
	void SetWarpObjectIndex(const uint32_t index) { warpObjectIndex_ = index; }
#pragma endregion


private:

	string railDataFileName_ = "";
	uint32_t warpObjectIndex_ = 0;
	uint32_t index_ = 0;

};
