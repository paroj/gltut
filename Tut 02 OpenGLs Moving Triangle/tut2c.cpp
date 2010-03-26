
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <glloader/gl_3_2_comp.h>
#include <GL/freeglut.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

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

GLuint theProgram;
GLuint positionAttrib;
GLuint elapsedTimeUniform;

const std::string strFragmentShader(
"#version 150\n"
"out vec4 outputColor;\n"
"void main()\n"
"{\n"
"   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n"
);

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(LoadShader(GL_VERTEX_SHADER, "tut2c.vert"));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));

	theProgram = CreateProgram(shaderList);

	positionAttrib = glGetAttribLocation(theProgram, "position");
	elapsedTimeUniform = glGetUniformLocation(theProgram, "time");

	GLuint loopDurationUnf = glGetUniformLocation(theProgram, "loopDuration");
	glUseProgram(theProgram);
	glUniform1f(loopDurationUnf, 5.0f);
	glUseProgram(0);
}

const float vertexPositions[] = {
	0.25f, 0.25f, 0.0f, 1.0f,
	0.25f, -0.25f, 0.0f, 1.0f,
	-0.25f, -0.25f, 0.0f, 1.0f,
};

GLuint positionBufferObject;
GLuint vao;


void InitializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);

	glUniform1f(elapsedTimeUniform, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(positionAttrib);
	glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	}
}


