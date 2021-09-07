#include "stdafx.h"
#include "PARS/Core/Timer.h"

namespace PARS
{
	Timer::Timer()
	{
		
	}

	Timer::~Timer()
	{

	}

	bool Timer::Initialize()
	{
		if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_Frequncy))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime);
			m_SecondsPerCount = 1.0f / m_Frequncy;
		}
		else
		{
			PARS_CRITICAL("Could not support Performance Timer");
			return false;
		}
		return true;
	}

	void Timer::Tick()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);

		m_DeltaTime = (m_CurrentTime - m_LastTime) * m_SecondsPerCount;
		m_LastTime = m_CurrentTime;

		m_FrameCount++;
		m_FPSDeltaTime += m_DeltaTime;

		if (m_FPSDeltaTime > 1.0f)
		{
			m_FrameRate = m_FrameCount;
			m_FrameCount = 0;
			m_FPSDeltaTime -= 1.0f;

			m_FuncFpsDeltaChanged(m_FrameRate);
		}
	}
}