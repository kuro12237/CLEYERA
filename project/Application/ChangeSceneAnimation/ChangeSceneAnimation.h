#pragma once
#include"Sprite/Sprite.h"
#include"Utility/ColorConverter/ColorConverter.h"

#include"TitleName2d/TitleName2d.h"
#include"BackTitle2d/TitleBack2d.h"
#include"RodingIcon2d/RodingIcon.h"

/// <summary>
/// ��ʑJ�ڃN���X
/// </summary>
class ChangeSceneAnimation
{
public:

	static ChangeSceneAnimation* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();


	/// <summary>
	/// imgui�X�V
	/// </summary>
	void ImGuiUpdate();


	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �\��
	/// </summary>
	void Draw();

	/// <summary>
	/// ��ʐؑփX�^�[�g
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

	//Singleton
	ChangeSceneAnimation() = default;
	~ChangeSceneAnimation() = default;
	ChangeSceneAnimation(const  ChangeSceneAnimation&) = delete;
	const  ChangeSceneAnimation& operator=(const  ChangeSceneAnimation&) = delete;
};
