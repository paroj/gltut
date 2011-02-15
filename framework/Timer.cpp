

#include <math.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include "framework.h"
#include "Timer.h"



namespace Framework
{
	Timer::Timer( Type eType, float fDuration )
		: m_eType(eType)
		, m_fDuration(fDuration)
		, m_bHasUpdated(false)
		, m_bIsPaused(false)
		, m_absPrevTime(0.0f)
		, m_fAccumTime(0.0f)
	{
		if(m_eType != TT_INFINITE)
			assert(m_fDuration > 0.0f);
	}

	void Timer::Reset()
	{
		m_bHasUpdated = false;
		m_fAccumTime = 0.0f;
	}

	bool Timer::TogglePause()
	{
		m_bIsPaused = !m_bIsPaused;
		return m_bIsPaused;
	}

	bool Timer::Update()
	{
		float absCurrTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
		if(!m_bHasUpdated)
		{
			m_absPrevTime = absCurrTime;
			m_bHasUpdated = true;
		}

		if(m_bIsPaused)
		{
			m_absPrevTime = absCurrTime;
			return false;
		}

		float fDeltaTime = absCurrTime - m_absPrevTime;
		m_fAccumTime += fDeltaTime;

		m_absPrevTime = absCurrTime;
		if(m_eType == TT_SINGLE)
			return m_fAccumTime > m_fDuration;

		return false;
	}

	float Timer::GetAlpha() const
	{
		switch(m_eType)
		{
		case TT_LOOP:
			return fmodf(m_fAccumTime, m_fDuration);
		case TT_SINGLE:
			return glm::clamp(m_fAccumTime / m_fDuration, 0.0f, 1.0f);
		}

		return -1.0f;	//Garbage.
	}

	float Timer::GetProgression() const
	{
		switch(m_eType)
		{
		case TT_LOOP:
			return fmodf(m_fAccumTime, m_fDuration) * m_fDuration;
		case TT_SINGLE:
			return glm::clamp(m_fAccumTime, 0.0f, m_fDuration);
		}

		return -1.0f;	//Garbage.
	}

	float Timer::GetTimeSinceStart() const
	{
		return m_fAccumTime;
	}
}
