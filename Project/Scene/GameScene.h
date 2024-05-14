#pragma once
#include"GameManager.h"
#include"GameObject/Sun/Sun.h"
#include"Utility/GameCollisionManager/GameCollisionManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Player/InputHandler/PlayerInputHandler.h"
#include"GameObject/Player/Camera/PlayerCamera.h"
#include"Utility/GameGravityManager/GameGravityManager.h"
#include"Utility/CollisionManager/CollisionManager.h"

#include"GameObject/WoodBlock/WoodBlock.h"
#include"GameObject/WoodBlock/WoodBlockManager.h"
#include"GameObject/Terrain/Terrain.h"
#include"GameObject/SkyDome/SkyDome.h"

#include"GameObject/Item/ItemManager.h"

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

	void LoadSounds();

	void CheckBlockCollision();
	void CheckCollision();

	void CheckGravitys();

	void MapObjectInitialize();
	void MapObjectUpdate();
	void MapObjectDraw();

	/// <summary>
	/// 当たった時のビネット処理
	/// </summary>
	void HitEffectUpdate();

	const string sceneName_ = "GameScene";

	CameraData cameraData_ = {};

	unique_ptr<PostEffect>postEffect_ = nullptr;

	bool IsVignatte_ = false;
	float vignatteTimer_ = 0.0f;

#pragma region map

	unique_ptr<Sun>sun_ = nullptr;
	unique_ptr<Terrain>terrain_ = nullptr;
	unique_ptr<SkyDome>skyDome_ = nullptr;

#pragma endregion

	unique_ptr<Player>player_ = nullptr;
	unique_ptr<PlayerInputHandler>playerInputHandler_ = nullptr;
	unique_ptr<PlayerCamera>playerCamera_ = nullptr;

	unique_ptr<WoodBlockManager>blockManager_ = nullptr;

	unique_ptr<ItemManager>itemManager_ = nullptr;

#pragma region Utility

	unique_ptr<GameGravityManager>gravityManager_ = nullptr;
	unique_ptr<GameCollisonManager>blockCollisionManager_ = nullptr;
	unique_ptr<CollisionManager>collsionManager_ = nullptr;

#pragma endregion

};


