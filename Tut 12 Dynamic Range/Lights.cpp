
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
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

const float g_fLightAttenuation = 1.0f / (15.0f * 15.0f);

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
	posValues.reserve(20);

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

	posValues.clear();
	posValues.push_back(glm::vec3(80.0f, 30.0f, -70.0f));
	posValues.push_back(glm::vec3(70.0f, 25.0f, 70.0f));
	m_lightPos[1].SetValues(posValues);
	m_lightTimers.push_back(Framework::Timer(Framework::Timer::TT_LOOP, 15.0f));

	posValues.clear();
	posValues.push_back(glm::vec3(-70.0f, 25.0f, -75.0f));
	posValues.push_back(glm::vec3(-70.0f, 5.0f, 0.0f));
	posValues.push_back(glm::vec3(-70.0f, 25.0f, 70.0f));
	posValues.push_back(glm::vec3(0.0f, 50.0f, 0.0f));
	m_lightPos[2].SetValues(posValues);
	m_lightTimers.push_back(Framework::Timer(Framework::Timer::TT_LOOP, 15.0f));
}

typedef std::pair<glm::vec4, float> LightVectorData;
typedef std::vector<LightVectorData> LightVectors;

glm::vec4 GetValue(const LightVectorData &data) {return data.first;}
float GetTime(const LightVectorData &data) {return data.second;}

void LightManager::SetSunlightValues( const std::vector<SunlightValue> &values )
{
	LightVectors ambient;
	LightVectors light;
	LightVectors background;

	for(size_t valIx = 0; valIx < values.size(); ++valIx)
	{
		ambient.push_back(LightVectorData(values[valIx].ambient, values[valIx].normTime));
		light.push_back(LightVectorData(values[valIx].sunlightIntensity, values[valIx].normTime));
		background.push_back(LightVectorData(values[valIx].backgroundColor, values[valIx].normTime));
	}

	m_ambientInterpolator.SetValues(ambient);
	m_sunlightInterpolator.SetValues(light);
	m_backgroundInterpolator.SetValues(background);
}

void LightManager::SetSunlightValues( SunlightValue *pValues, int iSize )
{
	LightVectors ambient;
	LightVectors light;
	LightVectors background;

	for(int valIx = 0; valIx < iSize; ++valIx)
	{
		ambient.push_back(LightVectorData(pValues[valIx].ambient, pValues[valIx].normTime));
		light.push_back(LightVectorData(pValues[valIx].sunlightIntensity, pValues[valIx].normTime));
		background.push_back(LightVectorData(pValues[valIx].backgroundColor, pValues[valIx].normTime));
	}

	m_ambientInterpolator.SetValues(ambient);
	m_sunlightInterpolator.SetValues(light);
	m_backgroundInterpolator.SetValues(background);
}

struct UpdateTimer
{
	void operator()(Framework::Timer &timer) {timer.Update();}
	void operator()(std::pair<const std::string, Framework::Timer> &timeData)
	{timeData.second.Update();}
};

struct PauseTimer
{
	void operator()(Framework::Timer &timer) {timer.TogglePause();}
	void operator()(std::pair<const std::string, Framework::Timer> &timeData)
	{timeData.second.TogglePause();}
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

bool LightManager::TogglePause()
{
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), PauseTimer());
	std::for_each(m_extraTimers.begin(), m_extraTimers.end(), PauseTimer());

	return m_sunTimer.TogglePause();
}

bool LightManager::ToggleSunPause()
{
	return m_sunTimer.TogglePause();
}

void LightManager::RewindTime( float secRewind )
{
	m_sunTimer.Rewind(secRewind);
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), RewindTimer(secRewind));
	std::for_each(m_extraTimers.begin(), m_extraTimers.end(), RewindTimer(secRewind));
}

void LightManager::FastForwardTime( float secFF )
{
	m_sunTimer.Fastforward(secFF);
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), FFTimer(secFF));
	std::for_each(m_extraTimers.begin(), m_extraTimers.end(), FFTimer(secFF));
}

LightBlock LightManager::GetLightPositions( const glm::mat4 &worldToCameraMat ) const
{
	LightBlock lightData;

	lightData.ambientIntensity = m_ambientInterpolator.Interpolate(m_sunTimer.GetAlpha());
	lightData.lightAttenuation = g_fLightAttenuation;

	float angle = 2.0f * 3.14159f * m_sunTimer.GetAlpha();
	glm::vec4 sunDirection(0.0f);
	sunDirection[0] = sinf(angle);
	sunDirection[1] = cosf(angle);

	//Keep the sun from being perfectly centered overhead.
	sunDirection = glm::rotate(glm::mat4(1.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * sunDirection;

	lightData.lights[0].cameraSpaceLightPos =
		worldToCameraMat * sunDirection;

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

float LightManager::GetSunTime() const
{
	return m_sunTimer.GetAlpha();
}
