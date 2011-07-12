///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2011-05-25
// Licence : This source is under MIT licence
// File    : test/gtc/quaternion.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/epsilon.hpp>

int test_quat_precision()
{
	int Error = 0;

	Error += sizeof(glm::lowp_quat) <= sizeof(glm::mediump_quat) ? 0 : 1;
	Error += sizeof(glm::mediump_quat) <= sizeof(glm::highp_quat) ? 0 : 1;
    
    return Error;
}

int test_quat_type()
{
    glm::quat A;
    glm::dquat B;
    
    return 0;
}

int main()
{
	int Error = 0;
    
	Error += test_quat_precision();
    Error += test_quat_type();

	return Error;
}
