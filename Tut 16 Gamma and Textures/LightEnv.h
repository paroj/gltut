
#ifndef LIGHT_ENVIRONMENT_H
#define LIGHT_ENVIRONMENT_H

#include <map>
#include <string>
#include "../framework/Timer.h"
#include <glm/glm.hpp>
#include "../framework/Interpolators.h"

//////////////////////////////////////////////////////////////////////////
//Lighting Environment
struct PerLight
{
	glm::vec4 cameraSpaceLightPos;
	glm::vec4 lightIntensity;
};

const int MAX_NUMBER_OF_LIGHTS = 4;

struct LightBlock
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float maxIntensity;
	float padding[2];
	PerLight lights[MAX_NUMBER_OF_LIGHTS];
};

class LightEnv
{
public:
	LightEnv(const std::string &envFilename);

	void UpdateTime();

	void TogglePause();

	void SetPause(bool pause = true);

	bool IsPaused() const
	{
		return m_sunTimer.IsPaused();
	}

	void RewindTime(float secRewind);

	void FastForwardTime(float secFF);

	glm::vec4 GetBackgroundColor() const
	{
		return m_backgroundInterpolator.Interpolate(m_sunTimer.GetAlpha());
	}

	float GetMaxIntensity() const
	{
		return m_maxIntensityInterpolator.Interpolate(m_sunTimer.GetAlpha());
	}

	glm::vec4 GetSunlightDirection() const;

	glm::vec4 GetSunlightIntensity() const
	{
		return m_sunlightInterpolator.Interpolate(m_sunTimer.GetAlpha());
	}

	glm::vec4 GetSunlightScaledIntensity() const;

	float GetElapsedTime() const
	{
		return m_sunTimer.GetProgression();
	}

	int GetNumLights() const;

	LightBlock GetLightBlock(const glm::mat4 &worldToCamera) const;

	int GetNumPointLights() const;
	glm::vec4 GetPointLightIntensity(int pointLightIx) const;
	glm::vec4 GetPointLightScaledIntensity(int pointLightIx) const;
	glm::vec3 GetPointLightWorldPos(int pointLightIx) const;

private:
	typedef Framework::ConstVelLinearInterpolator<glm::vec3> LightInterpolator;
	typedef std::map<std::string, Framework::Timer> ExtraTimerMap;

	float m_fLightAttenuation;

	Framework::Timer m_sunTimer;
	Framework::TimedLinearInterpolator<glm::vec4> m_ambientInterpolator;
	Framework::TimedLinearInterpolator<glm::vec4> m_backgroundInterpolator;
	Framework::TimedLinearInterpolator<glm::vec4> m_sunlightInterpolator;
	Framework::TimedLinearInterpolator<float> m_maxIntensityInterpolator;

	std::vector<LightInterpolator> m_lightPos;
	std::vector<glm::vec4> m_lightIntensity;
	std::vector<Framework::Timer> m_lightTimers;
};

#endif //LIGHT_ENVIRONMENT_H
