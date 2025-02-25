#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"
#include"Utility/ObjectManager/GameObjectManager.h"

#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Utility/convert/convert.h"

class ClearCamera :public ObjectComponent
{
public:
	ClearCamera() {}
	~ClearCamera() {}

	void Initialize()override;

	void Update()override;

#pragma region Get
	bool GetIsComplite() { return isComplete_; }
#pragma endregion

private:

	unique_ptr<SplineMotion>splineMotion_ = nullptr;
	bool isComplete_ = false;
	bool isStartFlag_ = false;

	uint32_t cameraIndex_ = 0;

	RailData railData_ = {};
};
