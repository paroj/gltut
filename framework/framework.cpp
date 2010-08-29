
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glloader/gl_3_2_comp.h>
#include <glloader/wgl_exts.h>
#include <glloader/gle.h>
#include <GL/freeglut.h>
#include "framework.h"


namespace Framework
{
	GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
	{
		GLuint shader = glCreateShader(eShaderType);
		const char *strFileData = strShaderFile.c_str();
		glShaderSource(shader, 1, &strFileData, NULL);

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			const char *strShaderType = NULL;
			switch(eShaderType)
			{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			}

			fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
	{
		std::string strFilename = "data\\" + strShaderFilename;
		std::ifstream shaderFile(strFilename.c_str());
		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		return CreateShader(eShaderType, shaderData.str());
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

	namespace
	{
		inline float DegToRad(float fAngDeg)
		{
			const float fDegToRad = 3.14159f * 2.0f / 360.0f;
			return fAngDeg * fDegToRad;
		}
	}

	void MatrixStack::Rotate( glm::vec3 &axisOfRotation, float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fInvCos = 1.0f - fCos;
		float fSin = sinf(fAngRad);
		float fInvSin = 1.0f - fSin;

		glm::vec3 axis = glm::normalize(axisOfRotation);

		glm::mat4 theMat(1.0f);
		theMat[0].x = (axis.x * axis.x) + ((1 - axis.x * axis.x) * fCos);
		theMat[1].x = axis.x * axis.y * (fInvCos) - (axis.z * fSin);
		theMat[2].x = axis.x * axis.z * (fInvCos) + (axis.y * fSin);

		theMat[0].y = axis.x * axis.y * (fInvCos) + (axis.z * fSin);
		theMat[1].y = (axis.y * axis.y) + ((1 - axis.y * axis.y) * fCos);
		theMat[2].y = axis.y * axis.z * (fInvCos) - (axis.x * fSin);

		theMat[0].z = axis.x * axis.z * (fInvCos) - (axis.y * fSin);
		theMat[1].z = axis.y * axis.z * (fInvCos) + (axis.x * fSin);
		theMat[2].z = (axis.z * axis.z) + ((1 - axis.z * axis.z) * fCos);
		m_currMat *= theMat;
	}

	void MatrixStack::RotateX( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[1].y = fCos; theMat[2].y = -fSin;
		theMat[1].z = fSin; theMat[2].z = fCos;

		m_currMat *= theMat;
	}

	void MatrixStack::RotateY( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[0].x = fCos; theMat[2].x = fSin;
		theMat[0].z = -fSin; theMat[2].z = fCos;
		m_currMat *= theMat;
	}

	void MatrixStack::RotateZ( float fAngDeg )
	{
		float fAngRad = DegToRad(fAngDeg);
		float fCos = cosf(fAngRad);
		float fSin = sinf(fAngRad);

		glm::mat4 theMat(1.0f);
		theMat[0].x = fCos; theMat[1].x = -fSin;
		theMat[0].y = fSin; theMat[1].y = fCos;
		m_currMat *= theMat;
	}

	void MatrixStack::Scale( const glm::vec3 &scaleVec )
	{
		glm::mat4 scaleMat(1.0f);
		scaleMat[0].x = scaleVec.x;
		scaleMat[1].y = scaleVec.y;
		scaleMat[2].z = scaleVec.z;

		m_currMat *= scaleMat;
	}

	void MatrixStack::Translate( const glm::vec3 &offsetVec )
	{
		glm::mat4 translateMat(1.0f);
		translateMat[3] = glm::vec4(offsetVec, 1.0f);

		m_currMat *= translateMat;
	}
}


void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
	/* add command line argument "classic" for a pre-3.x context */
	if ((argc != 2) || (strcmp (argv[1], "classic") != 0)) {
		glutInitContextVersion (3, 3);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (300, 200);
	glutCreateWindow (argv[0]);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	gleLoadFunctions();
	init();

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
