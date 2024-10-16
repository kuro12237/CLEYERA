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
	/// <summary>
	/// フレームと秒数を送る
	/// </summary>
	class RunTimeCounter
	{
	public:

		static RunTimeCounter* GetInstance();

		/// <summary>
		/// 作製
		/// </summary>
		void  Create();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 使用しない
		/// </summary>
		/// <param name="rootParamIndex"></param>
		void CommandCall(uint32_t rootParamIndex);

		/// <summary>
		/// 使用しない
		/// </summary>
		/// <param name="rootParamIndex"></param>
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
