#pragma once

class Player;
/// <summary>
/// �v���C���[�̃R�}���h�C���^�[�t�F�[�X
/// </summary>
class IPlayerCommand
{
public:
	IPlayerCommand() {};
	virtual ~IPlayerCommand() {};

	virtual void Exec(Player& p) = 0;

private:

};

