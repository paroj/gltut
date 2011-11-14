
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include "LightEnv.h"
#include "tinyxml.h"
#include <glload/gl_all.h>
#include "../framework/framework.h"
#include <glm/gtc/matrix_transform.hpp>


typedef std::pair<float, float> MaxIntensityData;
typedef std::vector<MaxIntensityData> MaxIntensityVector;
typedef std::pair<glm::vec4, float> LightData;
typedef std::vector<LightData> LightVector;

glm::vec4 GetValue(const LightData &data) {return data.first;}
float GetTime(const LightData &data) {return data.second;}
float GetValue(const MaxIntensityData &data) {return data.first;}
float GetTime(const MaxIntensityData &data) {return data.second;}

float distance(const glm::vec3 &lhs, const glm::vec3 &rhs)
{
	return glm::length(rhs - lhs);
}


namespace
{
	glm::vec4 ParseVec4(const std::string &strVec4)
	{
		std::stringstream strStream;
		strStream << strVec4;
		strStream.flush();
		glm::vec4 ret;
		strStream >> ret.x >> ret.y >> ret.z >> ret.w;
		return ret;
	}

	glm::vec3 ParseVec3(const std::string &strVec3)
	{
		std::stringstream strStream;
		strStream << strVec3;
		strStream.flush();
		glm::vec3 ret;
		strStream >> ret.x >> ret.y >> ret.z;
		return ret;
	}
}

LightEnv::LightEnv( const std::string& envFilename )
	: m_fLightAttenuation(40.0f)
{
	std::ifstream fileStream(envFilename.c_str());
	if(!fileStream.is_open())
		throw std::runtime_error("Could not find the mesh file.");

	TiXmlDocument theDoc;

	fileStream >> theDoc;
	fileStream.close();

	if(theDoc.Error())
		throw std::runtime_error(theDoc.ErrorDesc());

	TiXmlHandle docHandle(&theDoc);

	const TiXmlElement *pRootNode = docHandle.FirstChild("lightenv").ToElement();

	if(!pRootNode)
		throw std::runtime_error("The root node must be a 'lightenv' element.");

	pRootNode->QueryFloatAttribute("atten", &m_fLightAttenuation);
	m_fLightAttenuation = 1.0f / (m_fLightAttenuation * m_fLightAttenuation);

	const TiXmlElement *pSunNode = docHandle.FirstChild("lightenv").FirstChild("sun").ToElement();

	if(!pSunNode)
		throw std::runtime_error("There must be a 'lightenv' element that has a 'sun' element as a child.");

	float timerTime = 0;
	if(pSunNode->QueryFloatAttribute("time", &timerTime) != TIXML_SUCCESS)
		throw std::runtime_error("'sun' elements must have a 'time' attribute that is a float.");

	m_sunTimer = Framework::Timer(Framework::Timer::TT_LOOP, timerTime);

	LightVector ambient;
	LightVector light;
	LightVector background;
	MaxIntensityVector maxIntensity;

	for(const TiXmlElement *pKeyElem = pSunNode->FirstChildElement("key");
		pKeyElem;
		pKeyElem = pKeyElem->NextSiblingElement("key"))
	{
		float keyTime = 0;
		if(pKeyElem->QueryFloatAttribute("time", &keyTime) != TIXML_SUCCESS)
			throw std::runtime_error("'key' elements must have a 'time' attribute that is a float.");
		//Convert from hours to normalized time.
		keyTime = keyTime / 24.0f;

		std::string strVec4;
		if(pKeyElem->QueryStringAttribute("ambient", &strVec4) != TIXML_SUCCESS)
			throw std::runtime_error("'key' elements must have an 'ambient' attribute.");
		ambient.push_back(LightData(ParseVec4(strVec4), keyTime));

		if(pKeyElem->QueryStringAttribute("intensity", &strVec4) != TIXML_SUCCESS)
			throw std::runtime_error("'key' elements must have a 'intensity' attribute.");
		light.push_back(LightData(ParseVec4(strVec4), keyTime));

		if(pKeyElem->QueryStringAttribute("background", &strVec4) != TIXML_SUCCESS)
			throw std::runtime_error("'key' elements must have a 'background' attribute.");
		background.push_back(LightData(ParseVec4(strVec4), keyTime));

		maxIntensity.push_back(MaxIntensityData(0.0f, keyTime));
		if(pKeyElem->QueryFloatAttribute("max-intensity", &maxIntensity.back().first) != TIXML_SUCCESS)
			throw std::runtime_error("'key' elements must have a 'max-intensity' attribute that is a float.");
	}

	if(ambient.empty())
		throw std::runtime_error("'sun' element must have at least one 'key' element child.");

	m_ambientInterpolator.SetValues(ambient);
	m_sunlightInterpolator.SetValues(light);
	m_backgroundInterpolator.SetValues(background);
	m_maxIntensityInterpolator.SetValues(maxIntensity);

	const TiXmlElement *pLightNode = docHandle.FirstChild("lightenv").FirstChild("light").ToElement();
	for(; pLightNode; pLightNode = pLightNode->NextSiblingElement("light"))
	{
		if(m_lightPos.size() + 1 == MAX_NUMBER_OF_LIGHTS)
			throw std::runtime_error("Too many lights specified.");

		float lightTime = 0;
		if(pLightNode->QueryFloatAttribute("time", &lightTime) != TIXML_SUCCESS)
			throw std::runtime_error("'light' elements must have a 'time' attribute that is a float.");

		m_lightTimers.push_back(Framework::Timer(Framework::Timer::TT_LOOP, lightTime));

		std::string strVec4;
		if(pLightNode->QueryStringAttribute("intensity", &strVec4) != TIXML_SUCCESS)
			throw std::runtime_error("'light' elements must have an 'intensity' attribute.");
		m_lightIntensity.push_back(ParseVec4(strVec4));

		std::vector<glm::vec3> posValues;
		for(const TiXmlElement *pKeyElem = pLightNode->FirstChildElement("key");
			pKeyElem;
			pKeyElem = pKeyElem->NextSiblingElement("key"))
		{
			posValues.push_back(ParseVec3(pKeyElem->GetText()));
		}

		if(posValues.empty())
			throw std::runtime_error("'light' elements must have at least one 'key' element child.");

		m_lightPos.push_back(LightInterpolator());
		m_lightPos.back().SetValues(posValues);
	}
}

glm::vec4 LightEnv::GetSunlightDirection() const
{
	float angle = 2.0f * 3.14159f * m_sunTimer.GetAlpha();
	glm::vec4 sunDirection(0.0f);
	sunDirection[0] = sinf(angle);
	sunDirection[1] = cosf(angle);

	//Keep the sun from being perfectly centered overhead.
	sunDirection = glm::rotate(glm::mat4(1.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * sunDirection;

	return sunDirection;
}

glm::vec4 LightEnv::GetSunlightScaledIntensity() const
{
	return m_sunlightInterpolator.Interpolate(m_sunTimer.GetAlpha()) /
		m_maxIntensityInterpolator.Interpolate(m_sunTimer.GetAlpha());
}

int LightEnv::GetNumLights() const
{
	return 1 + m_lightPos.size();
}

int LightEnv::GetNumPointLights() const
{
	return m_lightPos.size();
}

glm::vec4 LightEnv::GetPointLightIntensity( int pointLightIx ) const
{
	return m_lightIntensity.at(pointLightIx);
}

glm::vec4 LightEnv::GetPointLightScaledIntensity( int pointLightIx ) const
{
	return m_lightIntensity.at(pointLightIx) /
		m_maxIntensityInterpolator.Interpolate(m_sunTimer.GetAlpha());
}

glm::vec3 LightEnv::GetPointLightWorldPos( int pointLightIx ) const
{
	return m_lightPos.at(pointLightIx).Interpolate(m_lightTimers.at(pointLightIx).GetAlpha());
}

LightBlock LightEnv::GetLightBlock( const glm::mat4 &worldToCamera ) const
{
	LightBlock lightData;
	lightData.ambientIntensity = m_ambientInterpolator.Interpolate(m_sunTimer.GetAlpha());
	lightData.lightAttenuation = m_fLightAttenuation;
	lightData.maxIntensity = m_maxIntensityInterpolator.Interpolate(m_sunTimer.GetAlpha());

	lightData.lights[0].cameraSpaceLightPos =
		worldToCamera * GetSunlightDirection();
	lightData.lights[0].lightIntensity = m_sunlightInterpolator.Interpolate(m_sunTimer.GetAlpha());

	for(size_t light = 0; light < m_lightPos.size(); light++)
	{
		glm::vec4 worldLightPos = glm::vec4(GetPointLightWorldPos(light), 1.0f);
		glm::vec4 lightPosCameraSpace = worldToCamera * worldLightPos;

		lightData.lights[light + 1].cameraSpaceLightPos = lightPosCameraSpace;
		lightData.lights[light + 1].lightIntensity = m_lightIntensity[light];
	}

	return lightData;
}

namespace
{
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
}

void LightEnv::UpdateTime()
{
	m_sunTimer.Update();
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), UpdateTimer());
}

void LightEnv::TogglePause()
{
	bool isPaused = m_sunTimer.TogglePause();
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), PauseTimer(isPaused));
}

void LightEnv::SetPause( bool pause )
{
	m_sunTimer.SetPause(pause);
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), PauseTimer(pause));
}

void LightEnv::RewindTime( float secRewind )
{
	m_sunTimer.Rewind(secRewind);
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), RewindTimer(secRewind));
}

void LightEnv::FastForwardTime( float secFF )
{
	m_sunTimer.Fastforward(secFF);
	std::for_each(m_lightTimers.begin(), m_lightTimers.end(), FFTimer(secFF));
}

