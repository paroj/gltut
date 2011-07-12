///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-01-15
// Updated : 2011-01-15
// Licence : This source is under MIT licence
// File    : test/core/func_matrix.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>

int test_matrixCompMult()
{


	return 0;
}

int test_outerProduct()
{


	return 0;
}

int test_transpose()
{


	return 0;
}

int test_determinant()
{


	return 0;
}

int test_inverse()
{
	int Failed(0);

	glm::mat4x4 A4x4(
		glm::vec4(1, 0, 1, 0), 
		glm::vec4(0, 1, 0, 0), 
		glm::vec4(0, 0, 1, 0), 
		glm::vec4(0, 0, 0, 1));
	glm::mat4x4 B4x4 = glm::inverse(A4x4);
	glm::mat4x4 I4x4 = A4x4 * B4x4;
	Failed += I4x4 == glm::mat4x4(1) ? 0 : 1;

	glm::mat3x3 A3x3(
		glm::vec3(1, 0, 1), 
		glm::vec3(0, 1, 0), 
		glm::vec3(0, 0, 1));
	glm::mat3x3 B3x3 = glm::inverse(A3x3);
	glm::mat3x3 I3x3 = A3x3 * B3x3;
	Failed += I3x3 == glm::mat3x3(1) ? 0 : 1;

	glm::mat2x2 A2x2(
		glm::vec2(1, 1), 
		glm::vec2(0, 1));
	glm::mat2x2 B2x2 = glm::inverse(A2x2);
	glm::mat2x2 I2x2 = A2x2 * B2x2;
	Failed += I2x2 == glm::mat2x2(1) ? 0 : 1;

	return Failed;
}


int main()
{
	int Failed = 0;
	Failed += test_matrixCompMult();
	Failed += test_outerProduct();
	Failed += test_transpose();
	Failed += test_determinant();
	Failed += test_inverse();
	return Failed;
}

