#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// �v���C���[�������
/// </summary>
class PlayerStateWalk :public IPlayerState
{
public:
	PlayerStateWalk() {};
	~PlayerStateWalk() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

	float flame_ = 0.0f;
};
