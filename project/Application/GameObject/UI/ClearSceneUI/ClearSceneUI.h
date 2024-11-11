#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"
#include"BottonsActions/ClearSceneJoyStick.h"
#include"BottonsControl/ClearSceneUIControl.h"
#include"BottonsActions/ClearSceneTitleText.h"

enum class ClearSceneChangeScene
{
	Title,
	Select,
	Next
};

/// <summary>
/// ÉQÅ[ÉÄíÜÇÃUI
/// </summary>
class ClearSceneUI :public ISceneUI
{
public:
	ClearSceneUI() {};
	~ClearSceneUI() {};

	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// çXêV
	/// </summary>
	void Update()override;

#pragma region Get
	bool GetIsSelect() { return isSelect_; }
	ClearSceneChangeScene GetNextStage() { return nextScene_; }
#pragma endregion


private:

	int32_t counter_ = 0;

	ClearSceneChangeScene nextScene_ = ClearSceneChangeScene::Title;

	unique_ptr<ClearSceneJoyStick>lJoyStick_ = nullptr;

	unique_ptr<ClearSceneUIBottonsControl>bottonControl_ = nullptr;
	vector<unique_ptr<ClearSceneTitleText>>texts_;

	bool isSelect_ = false;

};
