
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include "Lights.h"

static float g_fLightHeight = 5.5f;
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

LightManager::LightManager()
	: keyLightTimer(Framework::Timer::TT_LOOP, 5.0f)
	, ambientInterpolator(false, 5)
{
	ambientInterpolator.AppendValue(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	ambientInterpolator.AppendValue(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	ambientInterpolator.AppendValue(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
	ambientInterpolator.AppendValue(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
	ambientInterpolator.AppendValue(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
}

void LightManager::UpdateTime()
{
	keyLightTimer.Update();
}

bool LightManager::TogglePause()
{
	return keyLightTimer.TogglePause();
}

LightBlock LightManager::GetLightPositions( const glm::mat4 &worldToCameraMat ) const
{
	LightBlock lightData;

	lightData.ambientIntensity = ambientInterpolator.Interpolate(keyLightTimer.GetAlpha());
	lightData.lightAttenuation = g_fLightAttenuation;

	lightData.lights[0].cameraSpaceLightPos =
		worldToCameraMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	lightData.lights[0].lightIntensity = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

	for(int light = 1; light < NUMBER_OF_LIGHTS; light++)
	{
		glm::vec4 worldLightPos = CalcLightPosition(keyLightTimer,
			light * (1.0f / (NUMBER_OF_LIGHTS - 1)));
		glm::vec4 lightPosCameraSpace = worldToCameraMat * worldLightPos;

		lightData.lights[light].cameraSpaceLightPos = lightPosCameraSpace;
		lightData.lights[light].lightIntensity = glm::vec4(0.1f, 0.1f, 0.0f, 1.0f);
	}

	return lightData;
}

int LightManager::GetNumberOfPointLights() const
{
	return NUMBER_OF_LIGHTS - 1;
}

glm::vec3 LightManager::GetWorldLightPosition( int iLightIx ) const
{
	glm::vec4 worldLightPos = CalcLightPosition(keyLightTimer,
		iLightIx * (1.0f / (NUMBER_OF_LIGHTS - 1)));


	return glm::vec3(worldLightPos);
}
