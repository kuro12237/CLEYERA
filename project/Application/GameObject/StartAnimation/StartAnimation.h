#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"StartCount/StartCount.h"
#include"Utility/convert/convert.h"

class StartAnimation
{
public:
	StartAnimation() {};
	~StartAnimation() {};

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// point‚ğ•`‰æ
	/// </summary>
	void DebugLine();

	void Draw2d();

	void SetIsCountStart(const bool& flag) { isCountStart_ = flag; }


	bool GetIsGameStartFlag() { return isGameStart_; }
	bool GetIsStartFlag() { return isCountStart_; }

private:

	GameObjectManager* gameObjectManager_ = nullptr;

	vector<unique_ptr<SplineMotion>>splineMotions_;
	uint32_t splineMotionsMax_ = 2;
	vector<RailData>railData_;

	bool isGameStart_ = false;
	bool isCountStart_ = false;
	bool isStartCount_ = false;
	bool isCameraMotion_ = false;

	unique_ptr<StartCount>startCount_ = nullptr;

	string selectCameraName_ = "StartCamera";

};
