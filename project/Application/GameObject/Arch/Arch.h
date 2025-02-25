#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"state/IArchState.h"

/// <summary>
/// タイトルの扉
/// </summary>
class Arch :public ObjectComponent
{
public:
	Arch() {};
	~Arch() {};

	/// <summary>
	///  初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Set
	void SetStart(bool flag) { isStart_ = flag; }
	void SetCameraPos(const Math::Vector::Vector3& pos) { p_CameraPos_ = &pos; }
#pragma endregion

private:

	bool isStart_ = false;
	const Math::Vector::Vector3* p_CameraPos_ = nullptr;
};
