#include "Timer.h"


namespace dae
{
	float Time::m_DeltaTime = 0.0f;

	std::chrono::high_resolution_clock::time_point dae::Time::GetTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	float dae::Time::GetDeltaTime()
	{
		return m_DeltaTime;
	}

	void dae::Time::SetDeltaTime(float deltaTime)
	{
		m_DeltaTime = deltaTime;
	}
}


