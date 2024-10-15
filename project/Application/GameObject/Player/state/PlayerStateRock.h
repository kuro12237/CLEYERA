#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// ƒvƒŒƒCƒ„[Î‰»ó‘Ô
/// </summary>
class PlayerStateRock :public IPlayerState
{
public:
	PlayerStateRock() {};
	~PlayerStateRock() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

	float flame_ = 0;
	uint32_t timer_ = 0;
	uint32_t MaxTimer_ = 2;

	GameObjectManager* gameInst= nullptr;
};
