#pragma once
#include"IPlayerState.h"
#include"../Player.h"

/// <summary>
/// プレイヤージャンプ状態
/// </summary>
class PlayerStateFall :public IPlayerState
{
public:
	PlayerStateFall() {};
	~PlayerStateFall() {};

	void Initialize(Player* p)override;

	void Update(Player* p)override;

private:

};