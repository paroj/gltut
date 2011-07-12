///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2011-05-27
// Licence : This source is under MIT licence
// File    : test/gtc/type_ptr.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int test_make_pointer_mat()
{
    int Error = 0;

    float ArrayA[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int ArrayB[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    bool ArrayC[] = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false};
    
    glm::mat2x2 Mat2x2A = glm::make_mat2x2(ArrayA);
    glm::mat2x3 Mat2x3A = glm::make_mat2x3(ArrayA);
    glm::mat2x4 Mat2x4A = glm::make_mat2x4(ArrayA);
    glm::mat3x2 Mat3x2A = glm::make_mat3x2(ArrayA);
    glm::mat3x3 Mat3x3A = glm::make_mat3x3(ArrayA);
    glm::mat3x4 Mat3x4A = glm::make_mat3x4(ArrayA);
    glm::mat4x2 Mat4x2A = glm::make_mat4x2(ArrayA);
    glm::mat4x3 Mat4x3A = glm::make_mat4x3(ArrayA);
    glm::mat4x4 Mat4x4A = glm::make_mat4x4(ArrayA);
    
    return Error;
}

int test_make_pointer_vec()
{
    int Error = 0;
    
    float ArrayA[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int ArrayB[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    bool ArrayC[] = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false};
    
    glm::vec2 Vec2A = glm::make_vec2(ArrayA);
    glm::vec3 Vec3A = glm::make_vec3(ArrayA);
    glm::vec4 Vec4A = glm::make_vec4(ArrayA);
    
    glm::ivec2 Vec2B = glm::make_vec2(ArrayB);
    glm::ivec3 Vec3B = glm::make_vec3(ArrayB);
    glm::ivec4 Vec4B = glm::make_vec4(ArrayB);
  
    glm::bvec2 Vec2C = glm::make_vec2(ArrayC);
    glm::bvec3 Vec3C = glm::make_vec3(ArrayC);
    glm::bvec4 Vec4C = glm::make_vec4(ArrayC);
    
    return Error;
}

int main()
{
	int Error = 0;
    
    Error += test_make_pointer_vec();
    Error += test_make_pointer_mat();

	return Error;
}
