#pragma once
#include"BufferResources.h"
#include"Utility/DeltaTimer/DeltaTimer.h"

struct RunTimeCount
{
	float flame;
	uint32_t deltaTime;
};

class RunTimeCounter
{
public:

	static RunTimeCounter* GetInstance();

	void  Create();

	void Update();

	void CommandCall(uint32_t rootParamIndex);

	void ComputeCommandCall(uint32_t rootParamIndex);

#pragma region Get

	static RunTimeCount GetTimer() { return RunTimeCounter::GetInstance()->time_; }

#pragma endregion


private:


	unique_ptr<BufferResource<RunTimeCount>>timerBuf_ = nullptr;
	RunTimeCount time_;

	RunTimeCounter() = default;
	~RunTimeCounter() = default;
	RunTimeCounter(const  RunTimeCounter&) = delete;
	const  RunTimeCounter& operator=(const RunTimeCounter&) = delete;
};

