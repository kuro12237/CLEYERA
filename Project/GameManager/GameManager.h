#pragma once
#include"Cleyera.h"
#include"IScene.h"

#include"Utility/GlobalVariables/GlobalVariables.h"

#include"AnimationScene.h"
#include"TestLevelDataScene.h"

class GameManager
{
public:

	GameManager();
	~GameManager();

    void Run();
    void ChangeState(IScene *newScene);

private:

	IScene* Scene_ = nullptr;

};

