#pragma once
#include"GameManager.h"
#include"GameObject/WoodBlockManager/WoodBlockManager.h"
#include"GameObject/Sun/Sun.h"
#include"Utility/GameCollisionManager/GameCollisionManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Player/InputHandler/PlayerInputHandler.h"
#include"GameObject/Player/Camera/PlayerCamera.h"
#include"Utility/GameGravityManager/GameGravityManager.h"

class GameScene:public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;


private:

	void CheckBlockCollision();

	void CheckGravitys();

	void MapObjectInitialize();
	void MapObjectUpdate();
	void MapObjectDraw();

	const string sceneName_ = "GameScene";

	CameraData cameraData_ = {};

	unique_ptr<PostEffect>postEffect_ = nullptr;

#pragma region map

	unique_ptr<Sun>sun_ = nullptr;
#pragma endregion

	unique_ptr<Player>player_ = nullptr;
	unique_ptr<PlayerInputHandler>playerInputHandler_ = nullptr;
	unique_ptr<PlayerCamera>playerCamera_ = nullptr;

	unique_ptr<WoodBlockManager>woodBlockManager_ = nullptr;


#pragma region Utility


	unique_ptr<GameGravityManager>gravityManager_ = nullptr;
	unique_ptr<GameCollisonManager>blockCollisionManager_ = nullptr;
#pragma endregion
};


