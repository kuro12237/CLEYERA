#pragma once

class EnemyWalk;

/// <summary>
/// Enemy‚Ìó‘Ô‘JˆÚ
/// </summary>
class IEnemyWalkState
{
public:
	IEnemyWalkState() {};
	virtual ~IEnemyWalkState() {};

	virtual void Initialize([[maybe_unused]] EnemyWalk* e) = 0;

	virtual void Update([[maybe_unused]] EnemyWalk* e) = 0;

private:

};
