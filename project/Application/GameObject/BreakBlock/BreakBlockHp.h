#pragma once
#include"Pch.h"

/// <summary>
/// hpの管理
/// </summary>
class BreakBlockHp
{
public:
	BreakBlockHp() {};
	~BreakBlockHp() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int32_t hpCount=1);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();


	/// <summary>
	/// hp減算
	/// </summary>
	/// <param name="hpSub"></param>
	void SubtructHp(int32_t hpSub = -1);

#pragma region Get

	int32_t GetHpCount() { return hpCount_; }

#pragma endregion


private:

	int32_t hpCount_;

};
