
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Lights.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static float g_fLightHeight = 10.5f;
static float g_fLightRadius = 70.0f;

glm::vec4 CalcLightPosition(const Framework::Timer &timer, float alphaOffset)
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f;

	float timeThroughLoop = timer.GetAlpha() + alphaOffset;

	glm::vec4 ret(0.0f, g_fLightHeight, 0.0f, 1.0f);

	ret.x = cosf(timeThroughLoop * fScale) * g_fLightRadius;
	ret.z = sinf(timeThroughLoop * fScale) * g_fLightRadius;

	return ret;
}

const float g_fHalfLightDistance = 70.0f;
const float g_fLightAttenuation = 1.0f / (g_fHalfLightDistance * g_fHalfLightDistance);

float distance(const glm::vec3 &lhs, const glm::vec3 &rhs)
{
	return glm::length(rhs - lhs);
}

LightManager::LightManager()
	: m_sunTimer(Framework::Timer::TT_LOOP, 30.0f)
	, m_ambientInterpolator()
{
	m_lightTimers.reserve(NUMBER_OF_POINT_LIGHTS);
	m_lightPos.reserve(NUMBER_OF_POINT_LIGHTS);
	m_lightPos.push_back(LightInterpolator());
	m_lightPos.push_back(LightInterpolator());
	m_lightPos.push_back(LightInterpolator());

	m_lightIntensity.resize(NUMBER_OF_POINT_LIGHTS, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

	std::vector<glm::vec3> posValues;
	posValues.reserve(60);

	posValues.push_back(glm::vec3(-50.0f, 30.0f, 70.0f));
	posValues.push_back(glm::vec3(-70.0f, 30.0f, 50.0f));
	posValues.push_back(glm::vec3(-70.0f, 30.0f, -50.0f));
	posValues.push_back(glm::vec3(-50.0f, 30.0f, -70.0f));
	posValues.push_back(glm::vec3(50.0f, 30.0f, -70.0f));
	posValues.push_back(glm::vec3(70.0f, 30.0f, -50.0f));
	posValues.push_back(glm::vec3(70.0f, 30.0f, 50.0f));
	posValues.push_back(glm::vec3(50.0f, 30.0f, 70.0f));
	m_lightPos[0].SetValues(posValues);
	m_lightTimers.push_back(Framework::Timer(Framework::Timer::TT_LOOP, 15.0f));

	//Right-side light.
	posValues.clear();
	posValues.push_back(glm::vec3(100.0f, 6.0f, 75.0f));
	posValues.push_back(glm::vec3(90.0f, 8.0f, 90.0f));
	posValues.push_back(glm::vec3(75.0f, 10.0f, 100.0f));
	posValues.push_back(glm::vec3(60.0f, 12.0f, 90.0f));
	posValues.push_back(glm::vec3(50.0f, 14.0f, 75.0f));
	posValues.push_back(glm::vec3(60.0f, 16.0f, 60.0f));
	posValues.push_back(glm::vec3(75.0f, 18.0f, 50.0f));
	posValues.push_back(glm::vec3(90.0f, 20.0f, 60.0f));
	posValues.push_back(glm::vec3(100.0f, 22.0f, 75.0f));
	posValues.push_back(glm::vec3(90.0f, 24.0f, 90.0f));
	posValues.push_back(glm::vec3(75.0f, 26.0f, 100.0f));
	posValues.push_back(glm::vec3(60.0f, 28.0f, 90.0f));
	posValues.push_back(glm::vec3(50.0f, 30.0f, 75.0f));

	posValues.push_back(glm::vec3(105.0f, 9.0f, -70.0f));
	posValues.push_back(glm::vec3(105.0f, 10.0f, -90.0f));
	posValues.push_back(glm::vec3(72.0f, 20.0f, -90.0f));
	posValues.push_back(glm::vec3(72.0f, 22.0f, -70.0f));
	posValues.push_back(glm::vec3(105.0f, 32.0f, -70.0f));
	posValues.push_back(glm::vec3(105.0f, 34.0f, -90.0f));
	posValues.push_back(glm::vec3(72.0f, 44.0f, -90.0f));

	m_lightPos[1].SetValues(posValues);
	m_lightTimers.push_back(Framework::Timer(Framework::Timer::TT_LOOP, 25.0f));

	//Left-side light.
	posValues.clear();
	posValues.push_back(glm::vec3(-7.0f, 35.0f, 1.0f));
	posValues.push_back(glm::vec3(8.0f, 40.0f, -14.0f));
	posValues.push_back(glm::vec3(-7.0f, 45.0f, -29.0f));
	posValues.push_back(glm::vec3(-22.0f, 50.0f, -14.0f));
	posValues.push_back(glm::vec3(-7.0f, 55.0f, 1.0f));
	posValues.push_back(glm::vec3(8.0f, 60.0f, -14.0f));
	posValues.push_back(glm::vec3(-7.0f, 65.0f, -29.0f));

	posValues.push_back(glm::vec3(-83.0f, 30.0f, -92.0f));
	posValues.push_back(glm::vec3(-98.0f, 27.0f, -77.0f));
	posValues.push_back(glm::vec3(-83.0f, 24.0f, -62.0f));
	posValues.push_back(glm::vec3(-68.0f, 21.0f, -77.0f));
	posValues.push_back(glm::vec3(-83.0f, 18.0f, -92.0f));
	posValues.push_back(glm::vec3(-98.0f, 15.0f, -77.0f));

	posValues.push_back(glm::vec3(-50.0f, 8.0f, 25.0f));
	posValues.push_back(glm::vec3(-59.5f, 4.0f, 65.0f));
	posValues.push_back(glm::vec3(-59.5f, 4.0f, 78.0f));
	posValues.push_back(glm::vec3(-45.0f, 4.0f, 82.0f));
	posValues.push_back(glm::vec3(-40.0f, 4.0f, 50.0f));
	posValues.push_back(glm::vec3(-70.0f, 20.0f, 40.0f));
	posValues.push_back(glm::vec3(-60.0f, 20.0f, 90.0f));
	posValues.push_back(glm::vec3(-40.0f, 25.0f, 90.0f));

	m_lightPos[2].SetValues(posValues);
	m_lightTimers.push_back(Framework::Timer(Framework::Timer::TT_LOOP, 15.0f));
}

typedef std::pair<float, float> MaxIntensityData;
typedef std::vector<MaxIntensityData> MaxIntensityVector;
typedef std::pair<glm::vec4, float> LightVectorData;
typedef std::vector<LightVectorData> LightVector;

glm::vec4 GetValue(const LightVectorData &data) {return data.first;}
float GetTime(const LightVectorData &data) {return data.second;}
float GetValue(const MaxIntensityData &data) {return data.first;}
float GetTime(const MaxIntensityData &data) {return data.second;}

void LightManager::SetSunlightValues( SunlightValue *pValues, int iSize )
{
	LightVector ambient;
	LightVector light;
	LightVector background;

	for(int valIx = 0; valIx < iSize; ++valIx)
	{
		ambient.push_back(LightVectorData(pValues[valIx].ambient, pValues[valIx].normTime));
		light.push_back(LightVectorData(pValues[valIx].sunlightIntensity, pValues[valIx].normTime));
		background.push_back(LightVectorData(pValues[valIx].backgroundColor, pValues[valIx].normTime));
	}

	m_ambientInterpolator.SetValues(ambient);
	m_sunlightInterpolator.SetValues(light);
	m_backgroundInterpolator.SetValues(background);

	MaxIntensityVector maxIntensity;
	maxIntensity.push_back(MaxIntensityData(1.0f, 0.0f));
	m_maxIntensityInterpolator.SetValues(maxIntensity, false);
}

void LightManager::SetSunlightValues( SunlightValueHDR *pValues, int iSize )
{
	LightVector ambient;
	LightVector light;
	LightVector background;
	MaxIntensityVector maxIntensity;

	for(int valIx = 0; valIx < iSize; ++valIx)
	{
		ambient.push_back(LightVectorData(pValues[valIx].ambient, pValues[valIx].normTime));
		light.push_back(LightVectorData(pValues[valIx].sunlightIntensity, pValues[valIx].normTime));
		background.push_back(LightVectorData(pValues[valIx].backgroundColor, pValues[valIx].normTime));
		maxIntensity.push_back(MaxIntensityData(pValues[valIx].maxIntensity, pValues[valIx].normTime));
	}

	m_ambientInterpolator.SetValues(ambient);
	m_sunlightInterpolator.SetValues(light);
	m_backgroundInterpolator.SetValues(background);
	m_maxIntensityInterpolator.SetValues(maxIntensity);
}

struct UpdateTimer
{
	void operator()(Framework::Timer &timer) {timer.Update();}
	void operator()(std::pair<const std::string, Framework::Timer> &timeData)
	{timeData.second.Update();}
};

struct PauseTimer
{
	PauseTimer(bool _pause) : pause(_pause) {}
	void operator()(Framework::Timer &timer) {timer.SetPause(pause);}
	void operator()(std::pair<const std::string, Framework::Timer> &timeData)
	{timeData.second.SetPause(pause);}

	bool pause;
};

struct RewindTimer
{
	RewindTimer(float _secRewind) : secRewind(_secRewind) {}

	void operator()(Framework::Timer &timer) {timer.Rewind(secRewind);}
	void operator()(std::pair<const std::string, Framework::Timer> &timeData)
	{timeData.second.Rewind(secRewind);}

	float secRewind;
};

struct FFTimer
{
	FFTimer(float _secFF) : secFF(_secFF) {}

	void operator()(Framework::Timer &timer) {timer.Fastforward(secFF);}
	void operator()(std::pair<const std::string, Framework::Timer> &timeData)
	{timeData.second.Fastforward(secFF);}

	float secFF;
};

void LightManager::UpdateTime()
{
	m_sunTimer.Update();
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), UpdateTimer());
	std::for_each(m_extraTimers.begin(), m_extraTimers.end(), UpdateTimer());
}

void LightManager::SetPause(TimerTypes eTimer, bool pause)
{
	if(eTimer == TIMER_ALL || eTimer == TIMER_LIGHTS)
	{
		std::for_each(m_lightTimers.begin(), m_lightTimers.end(), PauseTimer(pause));
		std::for_each(m_extraTimers.begin(), m_extraTimers.end(), PauseTimer(pause));
	}

	if(eTimer == TIMER_ALL || eTimer == TIMER_SUN)
		m_sunTimer.TogglePause();
}

void LightManager::TogglePause( TimerTypes eTimer )
{
	SetPause(eTimer, !IsPaused(eTimer));
}

bool LightManager::IsPaused( TimerTypes eTimer ) const
{
	if(eTimer == TIMER_ALL || eTimer == TIMER_SUN)
		return m_sunTimer.IsPaused();

	return m_lightTimers.front().IsPaused();
}

void LightManager::RewindTime(TimerTypes eTimer, float secRewind )
{
	if(eTimer == TIMER_ALL || eTimer == TIMER_SUN)
		m_sunTimer.Rewind(secRewind);

	if(eTimer == TIMER_ALL || eTimer == TIMER_LIGHTS)
	{
		std::for_each(m_lightTimers.begin(), m_lightTimers.end(), RewindTimer(secRewind));
		std::for_each(m_extraTimers.begin(), m_extraTimers.end(), RewindTimer(secRewind));
	}
}

void LightManager::FastForwardTime(TimerTypes eTimer,  float secFF )
{
	if(eTimer == TIMER_ALL || eTimer == TIMER_SUN)
		m_sunTimer.Fastforward(secFF);

	if(eTimer == TIMER_ALL || eTimer == TIMER_LIGHTS)
	{
		std::for_each(m_lightTimers.begin(), m_lightTimers.end(), FFTimer(secFF));
		std::for_each(m_extraTimers.begin(), m_extraTimers.end(), FFTimer(secFF));
	}
}

LightBlock LightManager::GetLightInformation( const glm::mat4 &worldToCameraMat ) const
{
	LightBlock lightData;

	lightData.ambientIntensity = m_ambientInterpolator.Interpolate(m_sunTimer.GetAlpha());
	lightData.lightAttenuation = g_fLightAttenuation;

	lightData.lights[0].cameraSpaceLightPos =
		worldToCameraMat * GetSunlightDirection();
	lightData.lights[0].lightIntensity = m_sunlightInterpolator.Interpolate(m_sunTimer.GetAlpha());

	for(int light = 0; light < NUMBER_OF_POINT_LIGHTS; light++)
	{
		glm::vec4 worldLightPos =
			glm::vec4(m_lightPos[light].Interpolate(m_lightTimers[light].GetAlpha()), 1.0f);
		glm::vec4 lightPosCameraSpace = worldToCameraMat * worldLightPos;

		lightData.lights[light + 1].cameraSpaceLightPos = lightPosCameraSpace;
		lightData.lights[light + 1].lightIntensity = m_lightIntensity[light];
	}

	return lightData;
}


LightBlockHDR LightManager::GetLightInformationHDR( const glm::mat4 &worldToCameraMat ) const
{
	LightBlockHDR lightData;

	lightData.ambientIntensity = m_ambientInterpolator.Interpolate(m_sunTimer.GetAlpha());
	lightData.lightAttenuation = g_fLightAttenuation;
	lightData.maxIntensity = m_maxIntensityInterpolator.Interpolate(m_sunTimer.GetAlpha());

	lightData.lights[0].cameraSpaceLightPos =
		worldToCameraMat * GetSunlightDirection();
	lightData.lights[0].lightIntensity = m_sunlightInterpolator.Interpolate(m_sunTimer.GetAlpha());

	for(int light = 0; light < NUMBER_OF_POINT_LIGHTS; light++)
	{
		glm::vec4 worldLightPos =
			glm::vec4(m_lightPos[light].Interpolate(m_lightTimers[light].GetAlpha()), 1.0f);
		glm::vec4 lightPosCameraSpace = worldToCameraMat * worldLightPos;

		lightData.lights[light + 1].cameraSpaceLightPos = lightPosCameraSpace;
		lightData.lights[light + 1].lightIntensity = m_lightIntensity[light];
	}

	return lightData;
}

LightBlockGamma LightManager::GetLightInformationGamma( const glm::mat4 &worldToCameraMat ) const
{
	LightBlockHDR lightDataHdr = GetLightInformationHDR(worldToCameraMat);
	LightBlockGamma lightData;

	memcpy(&lightData, &lightDataHdr, sizeof(LightBlockGamma));

	return lightData;
}

glm::vec4 LightManager::GetSunlightDirection() const
{
	float angle = 2.0f * 3.14159f * m_sunTimer.GetAlpha();
	glm::vec4 sunDirection(0.0f);
	sunDirection[0] = sinf(angle);
	sunDirection[1] = cosf(angle);

	//Keep the sun from being perfectly centered overhead.
	sunDirection = glm::rotate(glm::mat4(1.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * sunDirection;

	return sunDirection;
}

glm::vec4 LightManager::GetSunlightIntensity() const
{
	return m_sunlightInterpolator.Interpolate(m_sunTimer.GetAlpha());
}

int LightManager::GetNumberOfPointLights() const
{
	return m_lightPos.size();
}

glm::vec3 LightManager::GetWorldLightPosition( int lightIx ) const
{
	return m_lightPos[lightIx].Interpolate(m_lightTimers[lightIx].GetAlpha());
}

void LightManager::SetPointLightIntensity( int iLightIx, const glm::vec4 &intensity )
{
	m_lightIntensity[iLightIx] = intensity;
}

glm::vec4 LightManager::GetPointLightIntensity( int iLightIx ) const
{
	return m_lightIntensity[iLightIx];
}

void LightManager::CreateTimer( const std::string &timerName,
							   Framework::Timer::Type eType, float fDuration )
{
	m_extraTimers[timerName] = Framework::Timer(eType, fDuration);
}

float LightManager::GetTimerValue( const std::string &timerName ) const
{
	ExtraTimerMap::const_iterator loc = m_extraTimers.find(timerName);

	if(loc == m_extraTimers.end())
		return -1.0f;

	return loc->second.GetAlpha();
}

glm::vec4 LightManager::GetBackgroundColor() const
{
	return m_backgroundInterpolator.Interpolate(m_sunTimer.GetAlpha());
}

float LightManager::GetMaxIntensity() const
{
	return m_maxIntensityInterpolator.Interpolate(m_sunTimer.GetAlpha());
}

float LightManager::GetSunTime() const
{
	return m_sunTimer.GetAlpha();
}
