#pragma once
#include"Utility/SplineMotion/SplineMotion.h"

#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"

/// <summary>
/// スタートのカメラの動き
/// </summary>
class StartCameraMotion :public ObjectComponent
{
public:
	StartCameraMotion() {};
	~StartCameraMotion() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="カメラ番号"></param>
	void Initilaize(const uint32_t &index);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバッグ用
	/// </summary>
	void DrawLines();

#pragma region Set

	void SetIsStartFlag(const bool& f) { isStartFlag_ = f; }

#pragma endregion


private:

	unique_ptr<SplineMotion>splineMotion_ = nullptr;
	bool isComplete_ = false;
	bool isStartFlag_ = false;

	uint32_t cameraIndex_ = 0;

	RailData railData_ = {};
};
