#pragma once
#include"Pch.h"
#include"GameObject/ObjectInterface/ISpriteData.h"

/// <summary>
/// UI�̒��ۃN���X
/// </summary>
class ISceneUI
{
public:
	ISceneUI() {};
	virtual ~ISceneUI() {};

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 2d�\��
	/// </summary>
	virtual void Draw2d() = 0;

private:

protected:

	vector<weak_ptr<ISpriteData>>sprites_;

};
