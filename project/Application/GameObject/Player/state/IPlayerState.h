#pragma once

class Player;
/// <summary>
/// Playerのインターフェース
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

