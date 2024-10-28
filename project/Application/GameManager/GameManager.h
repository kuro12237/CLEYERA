#pragma once
#include"Cleyera.h"
#include"IScene.h"

#include"Utility/GlobalVariables/GlobalVariables.h"

#include"GameScene.h"
#include"TitleScene.h"
#include"SelectScene.h"
#include"GameOverScene.h"

/// <summary>
/// �Q�[���Ǘ��N���X
/// </summary>
class GameManager
{
public:

	GameManager();
	~GameManager();

    /// <summary>
    /// ���s
    /// </summary>
    void Run();

    /// <summary>
    /// �V�[���ؑ�
    /// </summary>
    /// <param name="newScene"></param>
    void ChangeScene(unique_ptr<IScene>newScene);

private:

    unique_ptr<IScene>scene_ = nullptr;

};

