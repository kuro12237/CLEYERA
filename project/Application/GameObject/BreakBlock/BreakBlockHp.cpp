#include "BreakBlockHp.h"

void BreakBlockHp::Initialize(int32_t hpCount)
{
	hpCount_ = hpCount;
}

void BreakBlockHp::Update()
{

}

void BreakBlockHp::SubtructHp(int32_t hpSub)
{
	hpCount_ += hpSub;
}
