#pragma once

enum PLAYERGUNSTATE { STAND, RELOAD, ATTACK };



class PlayerGun;
class IPlayerGunState
{
public:
	IPlayerGunState() {};
	virtual ~IPlayerGunState() {};

	virtual void Initialize() = 0;

	virtual void Update(PlayerGun *gun) = 0;

	int GetstateNo() { return stateNo; };

private:

protected:

	static int stateNo;

};