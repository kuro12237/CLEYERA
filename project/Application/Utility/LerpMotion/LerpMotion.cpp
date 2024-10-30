#include"LerpMotion.h"

Math::Vector::Vector3 LerpMotion::LinearInterpolation()
{
	if (!isStartFlag_)
	{
		return {};
	}

	if (isComplete_)
	{
		return{};
	}
	const uint32_t kSelect = uint32_t(p_RailData_->size);

	// 2�̃|�C���g�̃C���f�b�N�X���擾
	size_t firstIndex = size_t(targetIndex_);
	size_t secondIndex = (firstIndex + 1) % kSelect;

	// 2�̃|�C���g�̈ʒu���擾
	const Math::Vector::Vector3& startPosition = p_RailData_->data[firstIndex].GetWorldPosition();
	const Math::Vector::Vector3& endPosition = p_RailData_->data[secondIndex].GetWorldPosition();

	// ���`��Ԃ��v�Z
	position_ = Math::Vector::Lerp(startPosition, endPosition, flame_);

	return position_;
}

Math::Vector::Vector3 LerpMotion::LinearInterpolationRotation()
{
	return Math::Vector::Vector3();
}

void LerpMotion::UpdateParamerter(const float& kFlame)
{
	const uint32_t kSelect = uint32_t(p_RailData_->size - 1);

	if (!isStartFlag_)
	{
		return;
	}

	if (isComplete_)
	{
		return;
	}

	///�C���f�b�N�X����������
	if (targetIndex_ >= kSelect)
	{
		isComplete_ = true;
		return;
	}

	if (targetIndex_ != kSelect)
	{
		flame_ += 1.0f / kFlame;

		if (flame_ >= 1.0f)
		{
			targetIndex_++;
			flame_ = 0.0f;
		}
	}
}
