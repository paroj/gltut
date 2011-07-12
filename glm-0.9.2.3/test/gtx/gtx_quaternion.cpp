///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-05-25
// Updated : 2011-05-31
// Licence : This source is under MIT licence
// File    : test/gtx/quaternion.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/epsilon.hpp>

int test_quat_mix()
{
	int Error = 0;
    
	glm::quat A = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
	glm::quat B = glm::angleAxis(90.0f, glm::vec3(0, 0, 1));
    glm::quat C = glm::mix(A, B, 0.5f);
    glm::quat D = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
    
    Error += glm::equalEpsilon(C.x, D.x, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.y, D.y, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.z, D.z, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.w, D.w, 0.01f) ? 0 : 1;
    
	return Error;
}

int test_quat_fastMix()
{
	int Error = 0;
    
	glm::quat A = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
	glm::quat B = glm::angleAxis(90.0f, glm::vec3(0, 0, 1));
    glm::quat C = glm::fastMix(A, B, 0.5f);
    glm::quat D = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
    
    Error += glm::equalEpsilon(C.x, D.x, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.y, D.y, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.z, D.z, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.w, D.w, 0.01f) ? 0 : 1;
    
	return Error;
}

int test_quat_shortMix()
{
	int Error = 0;
    
	glm::quat A = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
	glm::quat B = glm::angleAxis(90.0f, glm::vec3(0, 0, 1));
    glm::quat C = glm::shortMix(A, B, 0.5f);
    glm::quat D = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
    
    Error += glm::equalEpsilon(C.x, D.x, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.y, D.y, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.z, D.z, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.w, D.w, 0.01f) ? 0 : 1;
    
	return Error;
}

int test_quat_angleAxis()
{
	int Error = 0;

	glm::quat A = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
	glm::quat B = glm::angleAxis(90.0f, glm::vec3(0, 0, 1));
    glm::quat C = glm::mix(A, B, 0.5f);
    glm::quat D = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));

    Error += glm::equalEpsilon(C.x, D.x, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.y, D.y, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.z, D.z, 0.01f) ? 0 : 1;
	Error += glm::equalEpsilon(C.w, D.w, 0.01f) ? 0 : 1;

	return Error;
}

int test_quat_angle()
{
    int Error = 0;
    
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::equalEpsilon(L, 1.0f, 0.01f) ? 0 : 1;
        float A = glm::angle(N);
        Error += glm::equalEpsilon(A, 45.0f, 0.01f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::normalize(glm::vec3(0, 1, 1)));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::equalEpsilon(L, 1.0f, 0.01f) ? 0 : 1;
        float A = glm::angle(N);
        Error += glm::equalEpsilon(A, 45.0f, 0.01f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::normalize(glm::vec3(1, 2, 3)));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::equalEpsilon(L, 1.0f, 0.01f) ? 0 : 1;
        float A = glm::angle(N);
        Error += glm::equalEpsilon(A, 45.0f, 0.01f) ? 0 : 1;
    }
    
    return Error;
}

int test_quat_normalize()
{
    int Error = 0;
 
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::equalEpsilon(L, 1.0f, 0.000001f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(0, 0, 2));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::equalEpsilon(L, 1.0f, 0.000001f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(1, 2, 3));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::equalEpsilon(L, 1.0f, 0.000001f) ? 0 : 1;
    }

    return Error;
}

int main()
{
	int Error = 0;
    
    Error += test_quat_angle();
	Error += test_quat_angleAxis();
	Error += test_quat_mix();
    Error += test_quat_fastMix();
    Error += test_quat_shortMix();
    Error += test_quat_normalize();

	return Error;
}
