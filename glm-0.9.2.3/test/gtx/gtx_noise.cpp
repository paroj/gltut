///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-21
// Updated : 2011-04-26
// Licence : This source is under MIT licence
// File    : test/gtx/noise.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtx/noise.hpp>
#include <iostream>

int test_simplex()
{
	float ValueSNoise2D = glm::simplex(glm::vec2(0.5f));
    float ValueSNoise3D = glm::simplex(glm::vec3(0.5f));
    float ValueSNoise4D = glm::simplex(glm::vec4(0.5f));

	return 0;
}

int test_perlin()
{
	float ValueCNoise2D = glm::perlin(glm::vec2(0.5f));
    float ValueCNoise3D = glm::perlin(glm::vec3(0.5f));
    float ValueCNoise4D = glm::perlin(glm::vec4(0.5f));

	return 0;
}

int test_perlin_pedioric()
{
	float ValuePNoise2D = glm::perlin(glm::vec2(0.5f), glm::vec2(0.5f));
    float ValuePNoise3D = glm::perlin(glm::vec3(0.5f), glm::vec3(0.5f));
    float ValuePNoise4D = glm::perlin(glm::vec4(0.5f), glm::vec4(0.5f));

	return 0;
}

int main()
{
	int Error = 0;

	Error += test_simplex();
	Error += test_perlin();
	Error += test_perlin_pedioric();

	return Error;
}
