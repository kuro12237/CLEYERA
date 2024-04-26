#pragma once
#include"GameObject/Player/Player.h"
#include"IPlayerAudioCommand.h"

class PlayerAudioHandler
{
public:
	PlayerAudioHandler() {};
	~PlayerAudioHandler() {};

	void Handler();

	void CommandsExc(Player& player);

	void ImGuiUpdate();

private:

	std::queue<std::unique_ptr<IPlayerAudioCommand>>commands_{};

};
