#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// �v���C���[�W�����v���
/// </summary>
class PlayerStateJamp :public IPlayerState
{
public:
	PlayerStateJamp() {};
	~PlayerStateJamp() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

};
