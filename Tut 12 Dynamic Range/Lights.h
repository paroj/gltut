
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

struct LightBlock
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float padding[3];
	PerLight lights[NUMBER_OF_LIGHTS];
};

class LightManager
{
public:
	LightManager();

	void UpdateTime();

	bool TogglePause();

	LightBlock GetLightPositions(const glm::mat4 &worldToCameraMat) const;

	int GetNumberOfPointLights() const;
	glm::vec3 GetWorldLightPosition(int iLightIx) const;

	void CreateTimer(const std::string &timerName, Framework::Timer::Type eType, float fDuration);
	float GetTimerValue(const std::string &timerName) const;

private:
	typedef Framework::ConstVelLinearInterpolator<glm::vec3> LightInterpolator;
	typedef std::map<std::string, Framework::Timer> ExtraTimerMap;

	Framework::Timer m_keyLightTimer;
	Framework::LinearInterpolator<glm::vec4> m_ambientInterpolator;

	std::vector<LightInterpolator> m_lightPos;
	std::vector<Framework::Timer> m_lightTimers;
	ExtraTimerMap m_extraTimers;
};

#endif //LIGHTS_H
