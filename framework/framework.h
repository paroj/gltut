#ifndef FRAMEWORK_H
#define FRAMEWORK_H

namespace Framework
{
	GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);
}

#endif //FRAMEWORK_H
