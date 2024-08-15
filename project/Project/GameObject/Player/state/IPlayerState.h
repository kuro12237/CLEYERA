#pragma once

class Player;
class IPlayerState
{
public:
	IPlayerState() {};
	virtual ~IPlayerState() {};

	virtual void Initialize(Player* p =nullptr) = 0;

	virtual void Update(Player* p=nullptr) = 0;

private:

};

