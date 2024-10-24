#pragma once

class EnemyWalk;

/// <summary>
/// Enemyの状態遷移
/// </summary>
class IEnemyWalkState
{
public:
	IEnemyWalkState() {};
	virtual ~IEnemyWalkState() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="本体"></param>
	virtual void Initialize(EnemyWalk* e) = 0;


	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="本体"></param>
	virtual void Update(EnemyWalk* e) = 0;

private:

};
