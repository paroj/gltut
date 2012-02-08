
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <iostream>
#include "LightEnv.h"
#include <glload/gl_all.h>
#include "../framework/framework.h"
#include "rapidxml.hpp"
#include "rapidxml_helpers.h"
#include <glm/gtc/matrix_transform.hpp>

#define PARSE_THROW(cond, message)\
	if(!(cond))\
	throw std::runtime_error((message));

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

using rapidxml::xml_document;
using rapidxml::xml_node;
using rapidxml::xml_attribute;
using rapidxml::make_string;

namespace
{
	void ThrowAttrib(const xml_attribute<> &attrib, const std::string &msg)
	{
		std::string name = make_string(attrib);
		throw std::runtime_error("Attribute " + name + " " + msg);
	}

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

	std::vector<char> fileData;
	fileData.reserve(2000);
	fileData.insert(fileData.end(), std::istreambuf_iterator<char>(fileStream),
		std::istreambuf_iterator<char>());
	fileData.push_back('\0');

	xml_document<> doc;

	try
	{
		doc.parse<0>(&fileData[0]);
	}
	catch(rapidxml::parse_error &e)
	{
		std::cout << envFilename << ": Parse error in light environment file." << std::endl;
		std::cout << e.what() << std::endl << e.where<char>() << std::endl;
		throw;
	}

	xml_node<> *pRootNode = doc.first_node("lightenv");
	PARSE_THROW(pRootNode, ("lightenv node not found in light environment file: " + envFilename));

	m_fLightAttenuation = rapidxml::get_attrib_float(*pRootNode, "atten", m_fLightAttenuation);
	m_fLightAttenuation = 1.0f / (m_fLightAttenuation * m_fLightAttenuation);

	xml_node<> *pSunNode = pRootNode->first_node("sun");
	PARSE_THROW(pSunNode, "lightenv node must have a first child that is called `sun`.");

	m_sunTimer = Framework::Timer(Framework::Timer::TT_LOOP,
		rapidxml::get_attrib_float(*pSunNode, "time", ThrowAttrib));

	LightVector ambient;
	LightVector light;
	LightVector background;
	MaxIntensityVector maxIntensity;

	for(const xml_node<> *pKeyNode = pSunNode->first_node("key");
		pKeyNode;
		pKeyNode = pKeyNode->next_sibling("key"))
	{
		float keyTime = rapidxml::get_attrib_float(*pKeyNode, "time", ThrowAttrib);
		//Convert from hours to normalized time.
		keyTime = keyTime / 24.0f;

		ambient.push_back(LightData(
			rapidxml::get_attrib_vec4(*pKeyNode, "ambient", ThrowAttrib), keyTime));

		light.push_back(LightData(
			rapidxml::get_attrib_vec4(*pKeyNode, "intensity", ThrowAttrib), keyTime));

		background.push_back(LightData(
			rapidxml::get_attrib_vec4(*pKeyNode, "background", ThrowAttrib), keyTime));

		maxIntensity.push_back(MaxIntensityData(
			rapidxml::get_attrib_float(*pKeyNode, "max-intensity", ThrowAttrib), keyTime));
	}

	if(ambient.empty())
		throw std::runtime_error("'sun' element must have at least one 'key' element child.");

	m_ambientInterpolator.SetValues(ambient);
	m_sunlightInterpolator.SetValues(light);
	m_backgroundInterpolator.SetValues(background);
	m_maxIntensityInterpolator.SetValues(maxIntensity);

	for(xml_node<> *pLightNode = pRootNode->first_node("light");
		pLightNode;
		pLightNode = pLightNode->next_sibling("light"))
	{
		if(m_lightPos.size() + 1 == MAX_NUMBER_OF_LIGHTS)
			throw std::runtime_error("Too many lights specified.");

		m_lightTimers.push_back(Framework::Timer(
			Framework::Timer::TT_LOOP,
			rapidxml::get_attrib_float(*pLightNode, "time", ThrowAttrib)));

		m_lightIntensity.push_back(rapidxml::get_attrib_vec4(
			*pLightNode, "intensity", ThrowAttrib));

		std::vector<glm::vec3> posValues;
		for(xml_node<> *pKeyNode = pLightNode->first_node("key");
			pKeyNode;
			pKeyNode = pKeyNode->next_sibling("key"))
		{
			posValues.push_back(ParseVec3(make_string(*pKeyNode)));
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

