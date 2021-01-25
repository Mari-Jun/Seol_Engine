#pragma once

namespace PARS
{
	class Timer
	{
	public:
		Timer();
		virtual ~Timer();

		bool Initialize();
		void Tick();

		float GetDeltaTime() const { return m_DeltaTime; }
		UINT GetFrameRate() const { return m_FrameRate; }

	private:
		INT64 m_Frequncy = 0;
		INT64 m_CurrentTime = 0;
		INT64 m_LastTime = 0;
		UINT m_FrameRate = 0;
		UINT m_FrameCount = 0;
		float m_SecondsPerCount = 0.0f;
		float m_DeltaTime = 0.0f;
		float m_FPSDeltaTime = 0.0f;
	};
}


