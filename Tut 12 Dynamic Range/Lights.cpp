
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include "Lights.h"
#include <glm/glm.hpp>

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
	: m_keyLightTimer(Framework::Timer::TT_LOOP, 5.0f)
	, m_ambientInterpolator(true)
{
	std::vector<glm::vec4> ambientValues;
	ambientValues.reserve(4);
	
	ambientValues.push_back(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	m_ambientInterpolator.SetValues(ambientValues);

	m_lightTimers.reserve(NUMBER_OF_LIGHTS - 1);
	m_lightPos.reserve(NUMBER_OF_LIGHTS - 1);
	m_lightPos.push_back(LightInterpolator(true));
	m_lightPos.push_back(LightInterpolator(true));
	m_lightPos.push_back(LightInterpolator(true));

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

void LightManager::UpdateTime()
{
	m_keyLightTimer.Update();
	for(size_t loop = 0; loop < m_lightTimers.size(); loop++)
	{
		m_lightTimers[loop].Update();
	}
}

bool LightManager::TogglePause()
{
	for(size_t loop = 0; loop < m_lightTimers.size(); loop++)
	{
		m_lightTimers[loop].TogglePause();
	}

	return m_keyLightTimer.TogglePause();
}

LightBlock LightManager::GetLightPositions( const glm::mat4 &worldToCameraMat ) const
{
	LightBlock lightData;

	lightData.ambientIntensity = m_ambientInterpolator.Interpolate(m_keyLightTimer.GetAlpha());
	lightData.lightAttenuation = g_fLightAttenuation;

	lightData.lights[0].cameraSpaceLightPos =
		worldToCameraMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	lightData.lights[0].lightIntensity = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

	for(int light = 1; light < NUMBER_OF_LIGHTS; light++)
	{
		int lightIx = light - 1;
		glm::vec4 worldLightPos = glm::vec4(m_lightPos[lightIx].Interpolate(m_lightTimers[lightIx].GetAlpha()), 1.0f);
		glm::vec4 lightPosCameraSpace = worldToCameraMat * worldLightPos;

		lightData.lights[light].cameraSpaceLightPos = lightPosCameraSpace;
		lightData.lights[light].lightIntensity = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
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
