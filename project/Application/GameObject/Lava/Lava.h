#pragma once
#include"Lava.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"LavaParticle.h"

/// <summary>
/// 溶岩のオブジェくト制御クラス
/// </summary>
class Lava :public IObjectData
{
public:
	Lava() {};
	~Lava() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Set
	void SetCameraParent(const Math::Vector::Vector3& pos) { p_CameraPos_ = &pos; }
#pragma endregion

#pragma region Get

	LavaParticle* GetLavaParticle() { return lavaParticle_.get(); }

#pragma endregion


private:

	const Math::Vector::Vector3* p_CameraPos_ = nullptr;
	unique_ptr<LavaParticle>lavaParticle_ = nullptr;

};