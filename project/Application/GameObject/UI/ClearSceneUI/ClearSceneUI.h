#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"
#include"BottonsActions/ClearSceneJoyStick.h"
#include"BottonsControl/ClearSceneUIControl.h"
#include"BottonsActions/ClearSceneTitleText.h"
#include"BottonsActions/ClearSceneClearTextUi.h"

#include"../UIActiveParticle/UIActiveParticle.h"

enum class ClearSceneChangeScene
{
	Title,
	Select,
	Next
};

/// <summary>
/// クリア中のUI
/// </summary>
class ClearSceneUI :public ISceneUI
{
public:
	ClearSceneUI() {};
	~ClearSceneUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	void ParticleDraw2d()override;

#pragma region Get
	bool GetIsSelect() { return isSelect_; }
	ClearSceneChangeScene GetNextStage() { return nextScene_; }
#pragma endregion

#pragma region Set
	void SetStageCoin(const uint32_t stageCoinCount) { stageCoinCount_ = stageCoinCount; }
	void SetIsCearTextUIAnimStart(bool f) { clearText_->SetIsStart(f); }
#pragma endregion

private:

	int32_t counter_ = 0;

	ClearSceneChangeScene nextScene_ = ClearSceneChangeScene::Title;

	unique_ptr<ClearSceneJoyStick>lJoyStick_ = nullptr;

	unique_ptr<ClearSceneUIBottonsControl>bottonControl_ = nullptr;
	vector<shared_ptr<ClearSceneTitleText>>texts_;

	shared_ptr<ClearSceneClearTextUI>clearText_ = nullptr;

	unique_ptr<UIActiveParticle>uiActiveParticle_ = nullptr;

	bool isSelect_ = false;
	uint32_t stageCoinCount_ = 0;
};
