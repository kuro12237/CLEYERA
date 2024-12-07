#pragma once

class IGunEnemy;

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
	virtual void Initialize(IGunEnemy* e) = 0;


	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="本体"></param>
	virtual void Update(IGunEnemy* e) = 0;

private:

};
