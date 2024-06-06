#pragma once

#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"
#include"Game3dObject.h"
#include"TestScene.h"
#include"DebugTool/DebugCamera/DebugCamera.h"
#include"PostEffect/DeferrdShading/DeferredShading.h"
#include"Animation/AnimationManager.h"
#include"DebugTool/DebugSkeleton/DebugSkeleton.h"
#include"Model/primitive/Line.h"
#include"PostEffect/DeferrdShading/DeferredShading.h"
#include"GameObject/SkyDome/SkyDome.h"
#include"GameObject/Terrain/Terrain.h"

#include"GameObject/testObject/testObject.h"

#include"SceneFileLoder/SceneFileLoader.h"

class TestLevelDataScene :public IScene
{
public:
	TestLevelDataScene() {};
	~TestLevelDataScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:
	CameraData camera_{};
	unique_ptr<DebugCamera>debugCamera_ = nullptr;

	unique_ptr<PostEffect>postEffect_ = nullptr;

	LevelData* levelData_ = nullptr;

	PointLight_param light_{};

};
