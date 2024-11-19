#pragma once
#include"Cleyera.h"
#include"IScene.h"
#include"ISceneContext.h"

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

    /// <summary>
    /// �f�[�^���ړ�
    /// </summary>
    /// <param name="data"></param>
    void SetMoveSceneContext(unique_ptr<ISceneContext> data) { sceneContext_ = move(data); }

    /// <summary>
    /// �f�[�^�����
    /// </summary>
    /// <returns></returns>
    ISceneContext* GetMoveSceneContext() { return move(sceneContext_.get()); }

private:

    void ImGuiDebugPanelBegin();

    void ImGuiDebugPanelEnd();

    unique_ptr<IScene>scene_ = nullptr;
    unique_ptr<ISceneContext>sceneContext_ = nullptr;
};

