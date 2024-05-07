#pragma once


class Player;
class IPlayerState
{
public:

	IPlayerState() {};
	virtual ~IPlayerState() {};

	virtual void Initialize() = 0;

	virtual void Update(Player*player) = 0;

private:

};
