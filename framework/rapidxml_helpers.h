
#ifndef FRAMEWORK_RAPIDXML_HELPERS_H
#define FRAMEWORK_RAPIDXML_HELPERS_H

#include <string>
#include <sstream>
#include "rapidxml.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace rapidxml
{
	inline std::string make_string(const rapidxml::xml_base<> &data)
	{
		return std::string(data.value(), data.value_size());
	}

	inline std::string make_string_name(const rapidxml::xml_base<> &data)
	{
		return std::string(data.name(), data.name_size());
	}

	inline xml_node<> *next_element(xml_node<> *pNode)
	{
		pNode = pNode->next_sibling();
		while(pNode && pNode->type() != node_element)
			pNode = pNode->next_sibling();

		return pNode;
	}

	inline const xml_node<> *next_element(const xml_node<> *pNode)
	{
		pNode = pNode->next_sibling();
		while(pNode && pNode->type() != node_element)
			pNode = pNode->next_sibling();

		return pNode;
	}

	//If it's not there
	inline bool get_attrib_bool(const xml_node<> &node, const std::string &attribName, bool optRet = false)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			return optRet;

		const std::string &test = make_string(*pAttrib);
		if(test == "true")
			return true;

		return false;
	}

	template<typename Callable>
	int attrib_to_int(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istringstream inData(attrib.value());
		int ret;
		inData >> ret;
		if(inData.fail())
			FailFunc(attrib, "must be an integer.");

		return ret;
	}

	inline int attrib_to_int_opt(const xml_attribute<> &attrib, int optRet)
	{
		std::istringstream inData(attrib.value());
		int ret;
		inData >> ret;
		if(inData.fail())
			return optRet;

		return ret;
	}

	template<typename Callable>
	int get_attrib_int(const xml_node<> &node, const std::string &attribName, Callable FailFunc)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			throw std::runtime_error(attribName + " not found on node: " + make_string_name(node));

		return attrib_to_int(*pAttrib, FailFunc);
	}

	inline int get_attrib_int(const xml_node<> &node, const std::string &attribName, int optRet)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			return optRet;

		return attrib_to_int_opt(*pAttrib, optRet);
	}


	template<typename Callable>
	float attrib_to_float(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istringstream inData(attrib.value());
		float ret;
		inData >> ret;
		if(inData.fail())
			FailFunc(attrib, "must be a float.");

		return ret;
	}

	inline float attrib_to_float_opt(const xml_attribute<> &attrib, float optRet)
	{
		std::istringstream inData(attrib.value());
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

	inline float get_attrib_float(const xml_node<> &node, const std::string &attribName, float optRet)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			return optRet;

		return attrib_to_float_opt(*pAttrib, optRet);
	}

	template<typename Callable>
	glm::vec2 attrib_to_vec2(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::vec2 ret;
		inData >> ret.x >> ret.y;
		if(inData.fail())
			FailFunc(attrib, "must be a vec2.");

		return ret;
	}

	inline glm::vec2 attrib_to_vec2_opt(const xml_attribute<> &attrib, const glm::vec2 &optRet)
	{
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::vec2 ret;
		inData >> ret.x >> ret.y;
		if(inData.fail())
			return optRet;

		return ret;
	}


	template<typename Callable>
	glm::vec3 attrib_to_vec3(const xml_attribute<> &attrib, Callable FailFunc)
	{
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::vec3 ret;
		inData >> ret.x >> ret.y >> ret.z;
		if(inData.fail())
			FailFunc(attrib, "must be a vec3.");

		return ret;
	}

	inline glm::vec3 attrib_to_vec3_opt(const xml_attribute<> &attrib, const glm::vec3 &optRet)
	{
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::vec3 ret;
		inData >> ret.x >> ret.y >> ret.z;
		if(inData.fail())
			return optRet;

		return ret;
	}

	inline bool attrib_is_vec3(const xml_attribute<> &attrib)
	{
		std::istringstream inData(attrib.value());
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
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::vec4 ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			FailFunc(attrib, "must be a vec4.");

		return ret;
	}

	inline glm::vec4 attrib_to_vec4_opt(const xml_attribute<> &attrib, const glm::vec4 &optRet)
	{
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::vec4 ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			return optRet;

		return ret;
	}

	inline bool attrib_is_vec4(const xml_attribute<> &attrib)
	{
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::vec4 ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			return false;

		return true;
	}

	template<typename Callable>
	inline glm::vec4 get_attrib_vec4(const xml_node<> &node, const std::string &attribName, Callable FailFunc)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			throw std::runtime_error(attribName + " not found on node: " + make_string_name(node));

		return attrib_to_vec4(*pAttrib, FailFunc);
	}

	inline glm::vec4 get_attrib_vec4(const xml_node<> &node, const std::string &attribName,
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
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::fquat ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			FailFunc(attrib, "must be a quaternion.");

		return ret;
	}

	inline glm::fquat attrib_to_quat_opt(const xml_attribute<> &attrib, const glm::fquat &optRet)
	{
		std::istringstream inData(attrib.value());
		inData >> std::skipws;
		glm::fquat ret;
		inData >> ret.x >> ret.y >> ret.z >> ret.w;
		if(inData.fail())
			return optRet;

		return ret;
	}

	inline std::string get_attrib_string(const xml_node<> &node, const std::string &attribName)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			throw std::runtime_error(attribName + " not found on node: " + make_string_name(node));

		return make_string(*pAttrib);
	}

	inline std::string get_attrib_string(const xml_node<> &node, const std::string &attribName,
		const std::string &optRet)
	{
		const xml_attribute<> *pAttrib = node.first_attribute(attribName.c_str());
		if(!pAttrib)
			return optRet;

		return make_string(*pAttrib);
	}

}

#endif //FRAMEWORK_RAPIDXML_HELPERS_H
