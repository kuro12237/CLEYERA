#include "SplineMotion.h"

Math::Vector::Vector3 SplineMotion::CatmullRomInterpolation()
{

	const uint32_t kSelect = uint32_t(p_RailData_->size);
	return Math::Vector::Catmull_Rom(
		p_RailData_->data[(size_t(selectIndex_) - 1 + kSelect) % kSelect].translate,
		p_RailData_->data[size_t(selectIndex_)].translate,
		p_RailData_->data[(size_t(selectIndex_) + 1) % kSelect].translate,
		p_RailData_->data[(size_t(selectIndex_) + 2) % kSelect].translate,
		flame_
	);
}

void SplineMotion::UpdateParamerter(const float& kFlame)
{
}
