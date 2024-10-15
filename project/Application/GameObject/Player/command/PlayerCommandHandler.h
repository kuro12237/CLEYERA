#pragma once
#include"GameObject/Player/Player.h"

#include"PlayerJampCommand.h"
#include"PlayerMoveCommand.h"
#include"PlayerShootCommand.h"
#include"playerDashMoveCommand.h"

/// <summary>
/// �v���C���[����d����
/// </summary>
class PlayerCommandHandler
{
public:
	PlayerCommandHandler() {};
	~PlayerCommandHandler() {};

	/// <summary>
	/// �N���X�쐻
	/// </summary>
	void Handler();

	/// <summary>
	/// ���s
	/// </summary>
	/// <param name="player"></param>
	void CommandsExec(Player& player);

private:

	/// <summary>
	/// L�X�e�B�b�N���g���邩
	/// </summary>
	/// <returns></returns>
	bool IsLJoystickActive();

	queue<unique_ptr<IPlayerCommand>>commands_;

	float joystickThreshold_ = 0.2f;
};