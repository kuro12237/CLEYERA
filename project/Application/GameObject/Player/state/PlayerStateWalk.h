#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// �v���C���[�Ή����
/// </summary>
class PlayerStateWalk :public IPlayerState
{
public:
	PlayerStateWalk() {};
	~PlayerStateWalk() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

};
