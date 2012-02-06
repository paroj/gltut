
#ifndef FRAMEWORK_RAPIDXML_HELPERS_H
#define FRAMEWORK_RAPIDXML_HELPERS_H

#include <string>
#include <strstream>
#include "rapidxml.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace rapidxml
{
	std::string make_string(const rapidxml::xml_base<> &data)
	{
		return std::string(data.value(), data.value_size());
	}

	std::string make_string_name(const rapidxml::xml_base<> &data)
	{
		return std::string(data.name(), data.name_size());
	}

	template<typename Callable>
	int attrib_to_int(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		int ret;
		inData >> ret;
		if(inData.fail())
			FailFunc(attrib, "must be an integer.");

		return ret;
	}

	int attrib_to_int_opt(const xml_attribute<> &attrib, int optRet)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		int ret;
		inData >> ret;
		if(inData.fail())
			return optRet;

		return ret;
	}

	template<typename Callable>
	float attrib_to_float(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		float ret;
		inData >> ret;
		if(inData.fail())
			FailFunc(attrib, "must be a float.");

		return ret;
	}

	float attrib_to_float_ret(const xml_attribute<> &attrib, float optRet)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		float ret;
		inData >> ret;
		if(inData.fail())
			return optRet;

		return ret;
	}

	template<typename Callable>
	glm::vec3 attrib_to_vec3(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::vec3 ret;
		inData >> ret.x >> ret.y >> ret.z;
		if(inData.fail())
			FailFunc(attrib, "must be a vec3.");

		return ret;
	}

	glm::vec3 attrib_to_vec3_opt(const xml_attribute<> &attrib, const glm::vec3 &optRet)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::vec3 ret;
		inData >> ret.x >> ret.y >> ret.z;
		if(inData.fail())
			return optRet;

		return ret;
	}

	bool attrib_is_vec3(const xml_attribute<> &attrib)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::vec3 ret;
		inData >> ret.x >> ret.y >> ret.z;
		if(inData.fail())
			return false;

		return true;
	}


	template<typename Callable>
	glm::fquat attrib_to_quat(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::fquat ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			FailFunc(attrib, "must be a quaternion.");

		return ret;
	}

	glm::fquat attrib_to_quat_opt(const xml_attribute<> &attrib, const glm::fquat &optRet)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::fquat ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			return optRet;

		return ret;
	}

}

#endif //FRAMEWORK_RAPIDXML_HELPERS_H