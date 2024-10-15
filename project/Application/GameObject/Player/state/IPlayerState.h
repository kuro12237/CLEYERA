#pragma once

class Player;
/// <summary>
/// Player�̃C���^�[�t�F�[�X
/// </summary>
class IPlayerState
{
public:
	IPlayerState() {};
	virtual ~IPlayerState() {};

	virtual void Initialize(Player* p =nullptr) = 0;

	virtual void Update(Player* p=nullptr) = 0;

private:

};

