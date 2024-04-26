#include "AudioHandler.h"

void PlayerAudioHandler::Handler()
{

}

void PlayerAudioHandler::CommandsExc(Player& player)
{
	while (!commands_.empty()) {
		IPlayerAudioCommand* c = commands_.front().get();
		c->Exec(player);
		commands_.pop();
	}

}
