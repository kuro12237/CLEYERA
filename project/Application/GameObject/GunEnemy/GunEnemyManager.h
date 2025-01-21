#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"

#include"GunEnemy.h"
#include"GunEnemyPart.h"
#include"GameObject/ObjectInterface/ManagerComponent.h"

struct GunEnemyData
{
	bool empty = true;
	shared_ptr<GunEnemy>core = nullptr;
	vector<shared_ptr<GunEnemyPart>>parts;
	size_t partsSize = 3;

	void Reset() { core.reset(), parts.clear(); }
};

/// <summary>
/// 銃の敵管理クラス
/// </summary>
class GunEnemyManager :public ManagerComponent
{
public:
	GunEnemyManager() {};
	~GunEnemyManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="data"></param>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

#pragma region Get
	vector<GunEnemyData>GetGunEnemys() { return enemys_; }
#pragma endregion

#pragma region Set
	void setIsStartFlag(bool flag) { isGameStartFlag_ = flag; }
	bool GetIsStartFlag() { return isGameStartFlag_; }
	void SetWallHitParticleFunc(function<void(const Math::Vector::Vector3& pos, const Math::Vector::Vector3& velo)>func);

#pragma endregion

private:


	GameObjectManager* gameObjectManager_ = nullptr;

	uint32_t enemyCount_ = 0;

	vector<GunEnemyData>enemys_{};


	bool isGameStartFlag_ = false;
};

