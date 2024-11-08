#pragma once
#include"GameObject/Player/Player.h"
#include"GameObject/Player/state/IPlayerState.h"


/// <summary>
/// –³“G
/// </summary>
class PlayerStateInvincible :public IPlayerState
{
public:
	PlayerStateInvincible() {};
	~PlayerStateInvincible() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

};