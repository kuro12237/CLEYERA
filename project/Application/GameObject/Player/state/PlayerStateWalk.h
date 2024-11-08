#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// ƒvƒŒƒCƒ„[Î‰»ó‘Ô
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
