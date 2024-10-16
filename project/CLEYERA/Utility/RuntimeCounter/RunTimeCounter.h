#pragma once
#include"BufferResources.h"
#include"Utility/DeltaTimer/DeltaTimer.h"

struct RunTimeCount
{
	float flame;
	uint32_t deltaTime;
};

namespace Engine::Utility
{

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

		unique_ptr<Engine::Buffer::BufferResource<RunTimeCount>>timerBuf_ = nullptr;
		RunTimeCount time_;
		uint32_t max_ = 120;

		RunTimeCounter() = default;
		~RunTimeCounter() = default;
		RunTimeCounter(const  RunTimeCounter&) = delete;
		const  RunTimeCounter& operator=(const RunTimeCounter&) = delete;
	};
}
