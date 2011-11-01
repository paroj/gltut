

#include <math.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include "framework.h"
#include "Timer.h"



namespace Framework
{
	Timer::Timer( Type eType, float fDuration )
		: m_eType(eType)
		, m_secDuration(fDuration)
		, m_hasUpdated(false)
		, m_isPaused(false)
		, m_absPrevTime(0.0f)
		, m_secAccumTime(0.0f)
	{
		if(m_eType != TT_INFINITE)
			assert(m_secDuration > 0.0f);
	}

	void Timer::Reset()
	{
		m_hasUpdated = false;
		m_secAccumTime = 0.0f;
	}

	bool Timer::TogglePause()
	{
		m_isPaused = !m_isPaused;
		return m_isPaused;
	}

	bool Timer::IsPaused() const
	{
		return m_isPaused;
	}

	void Timer::SetPause( bool pause )
	{
		m_isPaused = pause;
	}

	bool Timer::Update()
	{
		float absCurrTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
		if(!m_hasUpdated)
		{
			m_absPrevTime = absCurrTime;
			m_hasUpdated = true;
		}

		if(m_isPaused)
		{
			m_absPrevTime = absCurrTime;
			return false;
		}

		float fDeltaTime = absCurrTime - m_absPrevTime;
		m_secAccumTime += fDeltaTime;

		m_absPrevTime = absCurrTime;
		if(m_eType == TT_SINGLE)
			return m_secAccumTime > m_secDuration;

		return false;
	}

	void Timer::Rewind( float secRewind )
	{
		m_secAccumTime -= secRewind;
		if(m_secAccumTime < 0.0f)
			m_secAccumTime = 0.0f;
	}

	void Timer::Fastforward( float secFF )
	{
		m_secAccumTime += secFF;
	}

	float Timer::GetAlpha() const
	{
		switch(m_eType)
		{
		case TT_LOOP:
			return fmodf(m_secAccumTime, m_secDuration) / m_secDuration;
		case TT_SINGLE:
			return glm::clamp(m_secAccumTime / m_secDuration, 0.0f, 1.0f);
		}

		return -1.0f;	//Garbage.
	}

	float Timer::GetProgression() const
	{
		switch(m_eType)
		{
		case TT_LOOP:
			return fmodf(m_secAccumTime, m_secDuration);
		case TT_SINGLE:
			return glm::clamp(m_secAccumTime, 0.0f, m_secDuration);
		}

		return -1.0f;	//Garbage.
	}

	float Timer::GetTimeSinceStart() const
	{
		return m_secAccumTime;
	}
}
