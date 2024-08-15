#pragma once

class Player;
class IPlayerCommand
{
public:
	IPlayerCommand() {};
	virtual ~IPlayerCommand() {};

	virtual void Exec(Player& p) = 0;

private:

};

