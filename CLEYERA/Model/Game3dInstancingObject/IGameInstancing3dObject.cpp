#include "IGameInstancing3dObject.h"

void IGameInstancing3dObject::Update()
{
	matrix_ = Math::Matrix::AffineMatrix(transform_.scale, transform_.rotate, transform_.translate);
}