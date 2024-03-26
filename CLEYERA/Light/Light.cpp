#include "Light.h"

void PointLight_param::UpdateMatrix()
{
	matrix = MatrixTransform::AffineMatrix({ 1,1,1 }, { 0,0,0 }, worldPos_);
}
