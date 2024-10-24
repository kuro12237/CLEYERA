#pragma once

class EnemyWalk;

/// <summary>
/// Enemy�̏�ԑJ��
/// </summary>
class IEnemyWalkState
{
public:
	IEnemyWalkState() {};
	virtual ~IEnemyWalkState() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="�{��"></param>
	virtual void Initialize(EnemyWalk* e) = 0;


	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="�{��"></param>
	virtual void Update(EnemyWalk* e) = 0;

private:

};
