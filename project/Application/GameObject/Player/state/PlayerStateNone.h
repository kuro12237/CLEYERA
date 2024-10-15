#pragma once
#include"GameObject/Player/Player.h"
#include"GameObject/Player/state/IPlayerState.h"

/// <summary>
/// •½í‚Ìˆ—
/// </summary>
class PlayerStateNone :public IPlayerState
{
public:
	PlayerStateNone() {};
	~PlayerStateNone() {};

	void Initialize(Player* p)override;

	void Update(Player * p)override;

private:
};

