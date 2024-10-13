#pragma once

#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectManager/GameObjectManager.h"

class TitleCamera :public IObjectData
{
public:
	TitleCamera() {};
	~TitleCamera() {};

	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize();

	/// <summary>
	/// çXêV
	/// </summary>
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

	float speed_ = 0.0f;

	float archStartOffset_ = 0.0f;
	float archOffsetAdd_ = 0.0f;

	bool isBridgeAnimationStart_ = false;
	size_t useBridgeNumber_ = 0;
	bool isCameraMove_ = true;
};
