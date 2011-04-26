
#ifndef LIGHTS_H
#define LIGHTS_H

#include <map>
#include "../framework/Timer.h"
#include <glm/glm.hpp>
#include "../framework/Interpolators.h"


struct PerLight
{
	glm::vec4 cameraSpaceLightPos;
	glm::vec4 lightIntensity;
};

const int NUMBER_OF_LIGHTS = 4;
const int NUMBER_OF_POINT_LIGHTS = NUMBER_OF_LIGHTS - 1;

struct LightBlock
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float padding[3];
	PerLight lights[NUMBER_OF_LIGHTS];
};

struct LightBlockHDR
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float maxIntensity;
	float padding[2];
	PerLight lights[NUMBER_OF_LIGHTS];
};

struct LightBlockGamma
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float maxIntensity;
	float gamma;
	float padding;
	PerLight lights[NUMBER_OF_LIGHTS];
};

struct SunlightValue
{
	float normTime;
	glm::vec4 ambient;
	glm::vec4 sunlightIntensity;
	glm::vec4 backgroundColor;
};

struct SunlightValueHDR
{
	float normTime;
	glm::vec4 ambient;
	glm::vec4 sunlightIntensity;
	glm::vec4 backgroundColor;
	float maxIntensity;
};

enum TimerTypes
{
	TIMER_SUN,
	TIMER_LIGHTS,
	TIMER_ALL,
	NUM_TIMER_TYPES,
};

class LightManager
{
public:
	LightManager();

	void SetSunlightValues(SunlightValue *pValues, int iSize);
	void SetSunlightValues(SunlightValueHDR *pValues, int iSize);

	void UpdateTime();
	void TogglePause(TimerTypes eTimer);
	void SetPause(TimerTypes eTimer, bool pause = true);
	bool IsPaused(TimerTypes eTimer) const;

	void RewindTime(TimerTypes eTimer, float secRewind);
	void FastForwardTime(TimerTypes eTimer, float secRewind);

	LightBlock GetLightInformation(const glm::mat4 &worldToCameraMat) const;
	LightBlockHDR GetLightInformationHDR(const glm::mat4 &worldToCameraMat) const;
	LightBlockGamma GetLightInformationGamma(const glm::mat4 &worldToCameraMat) const;

	glm::vec4 GetBackgroundColor() const;
	float GetMaxIntensity() const;

	glm::vec4 GetSunlightDirection() const;
	glm::vec4 GetSunlightIntensity() const;

	int GetNumberOfPointLights() const;
	glm::vec3 GetWorldLightPosition(int iLightIx) const;
	void SetPointLightIntensity(int iLightIx, const glm::vec4 &intensity);
	glm::vec4 GetPointLightIntensity(int iLightIx) const;

	void CreateTimer(const std::string &timerName, Framework::Timer::Type eType, float fDuration);
	float GetTimerValue(const std::string &timerName) const;
	float GetSunTime() const;

private:
	typedef Framework::ConstVelLinearInterpolator<glm::vec3> LightInterpolator;
	typedef std::map<std::string, Framework::Timer> ExtraTimerMap;

	Framework::Timer m_sunTimer;
	Framework::TimedLinearInterpolator<glm::vec4> m_ambientInterpolator;
	Framework::TimedLinearInterpolator<glm::vec4> m_backgroundInterpolator;
	Framework::TimedLinearInterpolator<glm::vec4> m_sunlightInterpolator;
	Framework::TimedLinearInterpolator<float> m_maxIntensityInterpolator;

	std::vector<LightInterpolator> m_lightPos;
	std::vector<glm::vec4> m_lightIntensity;
	std::vector<Framework::Timer> m_lightTimers;
	ExtraTimerMap m_extraTimers;
};

#endif //LIGHTS_H
