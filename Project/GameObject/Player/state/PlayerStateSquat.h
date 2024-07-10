#pragma once
#include"GameObject/Player/Player.h"
#include"GameObject/Player/state/IPlayerState.h"

class PlayerStateSquat :public IPlayerState
{
public:
	PlayerStateSquat() {};
	~PlayerStateSquat() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:
};