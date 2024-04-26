#pragma once

class Player;
class IPlayerAudioCommand
{
public:
	IPlayerAudioCommand() {};
	virtual ~IPlayerAudioCommand() {};

	virtual void Exec(Player& player) = 0;

private:

};