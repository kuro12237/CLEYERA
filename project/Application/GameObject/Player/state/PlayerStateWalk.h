#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// ƒvƒŒƒCƒ„[•à‚«ó‘Ô
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
