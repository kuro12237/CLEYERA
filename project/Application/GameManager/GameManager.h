#pragma once
#include"Cleyera.h"
#include"IScene.h"

#include"Utility/GlobalVariables/GlobalVariables.h"

#include"GameScene.h"
#include"TitleScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"

/// <summary>
/// ゲーム管理クラス
/// </summary>
class GameManager
{
public:

	GameManager();
	~GameManager();

    /// <summary>
    /// 実行
    /// </summary>
    void Run();

    /// <summary>
    /// シーン切替
    /// </summary>
    /// <param name="newScene"></param>
    void ChangeScene(unique_ptr<IScene>newScene);

private:

    unique_ptr<IScene>scene_ = nullptr;

};

