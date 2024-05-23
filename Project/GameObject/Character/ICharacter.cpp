#include "ICharacter.h"

void ICharacter::Draw(const CameraData& camera, const WorldTransform& wt)
{
	gameObject_->Draw(wt, camera);
}
