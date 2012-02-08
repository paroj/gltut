
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

	float attrib_to_float_opt(const xml_attribute<> &attrib, float optRet)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		float ret;
		inData >> ret;
		if(inData.fail())
			return optRet;

		return ret;
	}

	template<typename Callable>
	float get_attrib_float(const xml_node<> &node, const std::string &attribName, Callable FailFunc)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			throw std::runtime_error(attribName + " not found on node: " + make_string_name(node));

		return attrib_to_float(*pAttrib, FailFunc);
	}

	float get_attrib_float(const xml_node<> &node, const std::string &attribName, float optRet)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			return optRet;

		return attrib_to_float_opt(*pAttrib, optRet);
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
	glm::vec4 attrib_to_vec4(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::vec4 ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			FailFunc(attrib, "must be a vec4.");

		return ret;
	}

	glm::vec4 attrib_to_vec4_opt(const xml_attribute<> &attrib, const glm::vec4 &optRet)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::vec4 ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			return optRet;

		return ret;
	}

	bool attrib_is_vec4(const xml_attribute<> &attrib)
	{
		std::istrstream inData(attrib.value(), attrib.value_size());
		inData >> std::skipws;
		glm::vec4 ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			return false;

		return true;
	}

	template<typename Callable>
	glm::vec4 get_attrib_vec4(const xml_node<> &node, const std::string &attribName, Callable FailFunc)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			throw std::runtime_error(attribName + " not found on node: " + make_string_name(node));

		return attrib_to_vec4(*pAttrib, FailFunc);
	}

	glm::vec4 get_attrib_vec4(const xml_node<> &node, const std::string &attribName,
		const glm::vec4 &optRet)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			return optRet;

		return attrib_to_vec4_opt(*pAttrib, optRet);
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

	std::string get_attrib_string(const xml_node<> &node, const std::string &attribName)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			throw std::runtime_error(attribName + " not found on node: " + make_string_name(node));

		return make_string(*pAttrib);
	}

	std::string get_attrib_string(const xml_node<> &node, const std::string &attribName,
		const std::string &optRet)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			return optRet;

		return make_string(*pAttrib);
	}

}

#endif //FRAMEWORK_RAPIDXML_HELPERS_H