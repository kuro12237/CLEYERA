#pragma once

class PlayerReticle;
/// <summary>
/// ���e�B�N���̃R�}���h�C���^�[�t�F�[�X
/// </summary>
class IPlayerReticleCommand
{
public:
	IPlayerReticleCommand() {};
	virtual ~IPlayerReticleCommand() {};

	virtual void Exec(PlayerReticle& r) = 0;

private:


};
