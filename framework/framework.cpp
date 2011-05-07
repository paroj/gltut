
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <glload/gl_3_2_comp.h>
#include <glload/gll.h>
#include <GL/freeglut.h>
#include "framework.h"
#include "directories.h"


namespace Framework
{
	namespace
	{
		const char *GetShaderName(GLenum eShaderType)
		{
			switch(eShaderType)
			{
			case GL_VERTEX_SHADER: return "vertex"; break;
			case GL_GEOMETRY_SHADER: return "geometry"; break;
			case GL_FRAGMENT_SHADER: return "fragment"; break;
			}

			return NULL;
		}
	}

	GLuint CreateShader(GLenum eShaderType,
		const std::string &strShaderFile, const std::string &strShaderName)
	{
		GLuint shader = glCreateShader(eShaderType);
		const char *strFileData = strShaderFile.c_str();
		glShaderSource(shader, 1, (const GLchar**)&strFileData, NULL);

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			fprintf(stderr, "Compile failure in %s shader named \"%s\". Error:\n%s\n",
				GetShaderName(eShaderType), strShaderName.c_str(), strInfoLog);
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
	{
		std::string strFilename = LOCAL_FILE_DIR + strShaderFilename;
		std::ifstream shaderFile(strFilename.c_str());
		if(!shaderFile.is_open())
		{
			fprintf(stderr, "Cannot load the shader file \"%s\" for the %s shader.\n",
				strFilename.c_str(), GetShaderName(eShaderType));
			return 0;
		}
		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		return CreateShader(eShaderType, shaderData.str(), strShaderFilename);
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList)
	{
		GLuint program = glCreateProgram();

		for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
			glAttachShader(program, shaderList[iLoop]);

		glLinkProgram(program);

		GLint status;
		glGetProgramiv (program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		return program;
	}

	float DegToRad(float fAngDeg)
	{
		const float fDegToRad = 3.14159f * 2.0f / 360.0f;
		return fAngDeg * fDegToRad;
	}

}


void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

unsigned int defaults(unsigned int displayMode, int &width, int &height);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	int width = 500;
	int height = 500;
	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;
	displayMode = defaults(displayMode, width, height);

	glutInitDisplayMode (displayMode);
	glutInitContextVersion (3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitWindowSize (width, height); 
	glutInitWindowPosition (300, 200);
	glutCreateWindow (argv[0]);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	glload::LoadFunctions();
	init();

// 	glutMouseFunc(MouseButton);
// 	glutMotionFunc(MouseMotion);
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
