#pragma once
#include"../Arch.h"

/// <summary>
/// �X�e�[�g�C���^�[�t�F�[�X
/// </summary>
class IArchState
{
public:
	IArchState() {};
	~IArchState() {};

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize()=0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

private:

};
