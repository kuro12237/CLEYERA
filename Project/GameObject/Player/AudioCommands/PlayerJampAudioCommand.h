#pragma once
#include"IPlayerAudioCommand.h"

class PlayerJampAudioCommand : public IPlayerAudioCommand
{
public:
	PlayerJampAudioCommand() {};
	~PlayerJampAudioCommand() {};

	void Exec(Player& player)override;

private:

};