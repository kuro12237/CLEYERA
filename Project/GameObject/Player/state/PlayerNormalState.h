#pragma once
#include"IPlayerState.h"
#include"GameObject/Player/Player.h"

class PlayerNormaState:public IPlayerState
{
public:
	PlayerNormaState() {};
	~PlayerNormaState()override{};

	void Initialize()override;

	void Update(Player*player)override;
private:

};


