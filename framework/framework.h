#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <vector>
#include <string>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace Framework
{
	float DegToRad(float fAngDeg);

	GLuint CreateShader(GLenum eShaderType,
		const std::string &strShaderFile, const std::string &strShaderName);
	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);

	//Will *delete* the shaders given.
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);

	//Will find a file with the given base filename, either in the local directory or the global one.
	//If it doesn't, it will throw a std::runtime_error.
	std::string FindFileOrThrow(const std::string &strBasename);


}

#endif //FRAMEWORK_H
