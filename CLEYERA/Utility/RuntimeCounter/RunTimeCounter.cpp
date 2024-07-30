#include "RunTimeCounter.h"

RunTimeCounter* RunTimeCounter::GetInstance()
{
    static RunTimeCounter instance;
    return &instance;
}

void RunTimeCounter::Create()
{
    timerBuf_ = make_unique<BufferResource<RunTimeCount>>();
    timerBuf_->CreateResource();
}

void RunTimeCounter::Update()
{
    time_.deltaTime += DeltaTimer(time_.flame);

    timerBuf_->Map();
    timerBuf_->Setbuffer(time_);
    timerBuf_->UnMap();
}

void RunTimeCounter::CommandCall(uint32_t rootParamIndex)
{
    timerBuf_->CommandCall(rootParamIndex);
}
