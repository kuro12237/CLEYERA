#pragma once
#include"Game3dObject.h"

class PlayerGunBullet
{
public:
	PlayerGunBullet() {};
	~PlayerGunBullet() {};

	void Initalize();

	void Update();

	void Draw(const CameraData& camera);

private:



};