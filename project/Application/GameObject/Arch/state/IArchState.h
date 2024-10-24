#pragma once
#include"../Arch.h"

/// <summary>
/// ステートインターフェース
/// </summary>
class IArchState
{
public:
	IArchState() {};
	~IArchState() {};

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize()=0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

private:

};
