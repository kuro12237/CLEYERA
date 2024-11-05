#pragma once
#include"Pch.h"
#include"GameObject/ObjectInterface/ISpriteData.h"

/// <summary>
/// UIの抽象クラス
/// </summary>
class ISceneUI
{
public:
	ISceneUI() {};
	virtual ~ISceneUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 2d表示
	/// </summary>
	virtual void Draw2d() = 0;

private:

protected:

	vector<weak_ptr<ISpriteData>>sprites_;

};
