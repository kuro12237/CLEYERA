#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"
#include"BottonsActions/ClearSceneJoyStick.h"
#include"BottonsControl/ClearSceneUIControl.h"
#include"BottonsActions/ClearSceneTitleText.h"
#include"BottonsActions/ClearSceneCoinUI.h"


enum class ClearSceneChangeScene
{
	Title,
	Select,
	Next
};

/// <summary>
/// �Q�[������UI
/// </summary>
class ClearSceneUI :public ISceneUI
{
public:
	ClearSceneUI() {};
	~ClearSceneUI() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

#pragma region Get
	bool GetIsSelect() { return isSelect_; }
	ClearSceneChangeScene GetNextStage() { return nextScene_; }
#pragma endregion

#pragma region Set
	void SetStageCoin(const uint32_t stageCoinCount) { stageCoinCount_ = stageCoinCount; }
#pragma endregion

private:

	int32_t counter_ = 0;

	ClearSceneChangeScene nextScene_ = ClearSceneChangeScene::Title;

	unique_ptr<ClearSceneJoyStick>lJoyStick_ = nullptr;

	unique_ptr<ClearSceneUIBottonsControl>bottonControl_ = nullptr;
	vector<unique_ptr<ClearSceneTitleText>>texts_;

	vector<shared_ptr<ClearSceneCoinUI>>coins_;

	bool isSelect_ = false;
	uint32_t stageCoinCount_ = 0;
};