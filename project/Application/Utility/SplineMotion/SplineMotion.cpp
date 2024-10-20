#include "SplineMotion.h"

Math::Vector::Vector3 SplineMotion::CatmullRomInterpolation()
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
	position_ = Math::Vector::Catmull_Rom(
		p_RailData_->data[(size_t(targetIndex_) - 1 + kSelect) % kSelect].GetWorldPosition(),
		p_RailData_->data[size_t(targetIndex_)].GetWorldPosition(),
		p_RailData_->data[(size_t(targetIndex_) + 1) % kSelect].GetWorldPosition(),
		p_RailData_->data[(size_t(targetIndex_) + 2) % kSelect].GetWorldPosition(),
		flame_
	);
	return position_;
}

Math::Vector::Vector3 SplineMotion::CalculateSplineRotation()
{
	if (!isStartFlag_)
	{
		return {};
	}

	Math::Vector::Vector3 result{};
	if (!p_Target_)
	{
		return result;
	}

	Math::Vector::Vector3 rotate = Math::Vector::Normalize(Math::Vector::Subtruct(*p_Target_, position_));

	result.x = Math::Vector::CalcXRotation(rotate);
	result.y = Math::Vector::CalcYRotation(rotate);
	return result;
}

void SplineMotion::UpdateParamerter(const float& kFlame)
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

	///インデックスが超えたら
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
