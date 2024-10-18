#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"

/// <summary>
/// �X�v���C���Ȑ������邽�߂̃N���X
/// </summary>
class SplineMotion
{
public:
	SplineMotion() {};
	~SplineMotion() {};

	/// <summary>
	/// �X�v���C���Ȑ���Ԋ֐�
	/// </summary>
	Math::Vector::Vector3 CatmullRomInterpolation();

	/// <summary>
	/// �p�����[�^�[�̍X�V
	/// </summary>
	/// <param name="�t���[��Max�l"></param>
	void UpdateParamerter(const float &kFlame);

#pragma region Get


#pragma endregion



private:

	const RailData* p_RailData_ = nullptr;

	uint32_t selectIndex_ = 0;

	float flame_ = 0.0f;

	bool isComplete_ = false;

};

