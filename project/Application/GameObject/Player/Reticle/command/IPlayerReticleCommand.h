#pragma once

class PlayerReticle;
/// <summary>
/// レティクルのコマンドインターフェース
/// </summary>
class IPlayerReticleCommand
{
public:
	IPlayerReticleCommand() {};
	virtual ~IPlayerReticleCommand() {};

	virtual void Exec(PlayerReticle& r) = 0;

private:


};
