#pragma once

class GunEnemy;

/// <summary>
/// Enemyの状態遷移
/// </summary>
class IGunEnemyState
{
public:
	IGunEnemyState() {};
	virtual ~IGunEnemyState() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="本体"></param>
	virtual void Initialize(GunEnemy* e) = 0;


	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="本体"></param>
	virtual void Update(GunEnemy* e) = 0;

private:

};
