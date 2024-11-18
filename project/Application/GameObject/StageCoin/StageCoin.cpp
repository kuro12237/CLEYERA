#include "StageCoin.h"

void StageCoin::Initilaize()
{
	INameable::name_ = "StageCoin"+FormatNumberWithDots(coinNumber_);
}

void StageCoin::Update()
{

}

void StageCoin::OnCollision(ICollider* c, IObjectData* objData)
{
	c;
	objData;
	isDead_ = true;
}
