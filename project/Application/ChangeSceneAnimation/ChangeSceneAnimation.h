#pragma once
#include"Sprite/Sprite.h"
#include"Utility/ColorConverter/ColorConverter.h"

#include"TitleName2d/TitleName2d.h"
#include"BackTitle2d/TitleBack2d.h"
#include"RodingIcon2d/RodingIcon.h"

/// <summary>
/// 画面遷移クラス
/// </summary>
class ChangeSceneAnimation
{
public:

	static ChangeSceneAnimation* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();


	/// <summary>
	/// imgui更新
	/// </summary>
	void ImGuiUpdate();


	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 表示
	/// </summary>
	void Draw();

	/// <summary>
	/// 画面切替スタート
	/// </summary>
	void ChangeStart();
	 
#pragma region Get
	bool GetEnd() { return isEndFlag_; }
	bool GetIsComplite() { return isCompliteFlag_; }
	bool GetIsChangeSceneFlag() { return isChangeSceneFlag_; }
#pragma endregion

private:

	bool isEndFlag_ = false;
	bool isStartFlag_ = false;
	bool isCompliteFlag_ = true;

	bool isChangeSceneFlag_ = false;

	bool isUpdateFlag_ = false;

	float flame_ = 0.0f;
	float flameMax_ = 120.0f;

	vector<uint32_t>noiseTex_ = {};
	float dissolveMax_ = 1.0f;
	float dissolveMask_ = 1.0f;

	unique_ptr<TitleName2d>titleName2d_ = nullptr;
	unique_ptr<TitleBack2d>titleBack2d_ = nullptr;
	unique_ptr<RodingIcon2d>rodingIcon_ = nullptr;
	
	bool initializeLock_ = false;


private:

	//Singleton
	ChangeSceneAnimation() = default;
	~ChangeSceneAnimation() = default;
	ChangeSceneAnimation(const  ChangeSceneAnimation&) = delete;
	const  ChangeSceneAnimation& operator=(const  ChangeSceneAnimation&) = delete;
};
