#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"

class TitleCamera :public IObjectData
{
public:
	TitleCamera() {};
	~TitleCamera() {};

	void Initialize();

	void Update();

#pragma region Set

	void SetIsCameraMove(bool flag) { isCameraMove_ = flag; }

#pragma endregion

#pragma region Get

	bool GetIsBridgeAnimationStart() {return isBridgeAnimationStart_;}
	size_t GetUseBridgeNumber() { return useBridgeNumber_; }
    float GetArchStartOffset() { return archStartOffset_; }
#pragma endregion

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	float speed_ = 0.06f;

	float archStartOffset_ = 0.0f;

	bool isBridgeAnimationStart_ = false;
	size_t useBridgeNumber_ = 0;
	bool isCameraMove_ = true;
};
