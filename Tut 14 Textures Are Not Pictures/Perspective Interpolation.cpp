#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <glutil/glutil.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MousePole.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;

	GLuint cameraToClipMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_SmoothInterp;
ProgramData g_LinearInterp;

ProgramData LoadProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.cameraToClipMatrixUnif = glGetUniformLocation(data.theProgram, "cameraToClipMatrix");

	return data;
}

void InitializePrograms()
{
	g_SmoothInterp = LoadProgram("SmoothVertexColors.vert", "SmoothVertexColors.frag");
	g_LinearInterp = LoadProgram("NoCorrectVertexColors.vert", "NoCorrectVertexColors.frag");

	glutil::MatrixStack persMatrix;
	persMatrix.Perspective(60.0f, 1.0f, g_fzNear, g_fzFar);

	glUseProgram(g_SmoothInterp.theProgram);
	glUniformMatrix4fv(g_SmoothInterp.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUseProgram(g_LinearInterp.theProgram);
	glUniformMatrix4fv(g_LinearInterp.cameraToClipMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(persMatrix.Top()));
	glUseProgram(0);
}

Framework::Mesh *g_pRealHallway = NULL;
Framework::Mesh *g_pFauxHallway = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pRealHallway = new Framework::Mesh("RealHallway.xml");
		g_pFauxHallway = new Framework::Mesh("FauxHallway.xml");
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}
}

static bool g_bUseFakeHallway = false;
static bool g_bUseSmoothInterpolation = true;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pRealHallway && g_pFauxHallway)
	{
		if(g_bUseSmoothInterpolation)
			glUseProgram(g_SmoothInterp.theProgram);
		else
			glUseProgram(g_LinearInterp.theProgram);

		if(g_bUseFakeHallway)
			g_pFauxHallway->Render();
		else
			g_pRealHallway->Render();

		glUseProgram(0);
	}

	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glutPostRedisplay();
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
		delete g_pRealHallway;
		delete g_pFauxHallway;
		glutLeaveMainLoop();
		return;

	case 's':
	case 'S':
		g_bUseFakeHallway = !g_bUseFakeHallway;
		if(g_bUseFakeHallway)
			printf("Fake Hallway.\n");
		else
			printf("Real Hallway.\n");
		break;

	case 'p':
	case 'P':
		g_bUseSmoothInterpolation = !g_bUseSmoothInterpolation;
		if(g_bUseSmoothInterpolation)
			printf("Perspective correct interpolation.\n");
		else
			printf("Just linear interpolation.\n");
		break;

	case 32:
		//Reload.
		delete g_pRealHallway;
		delete g_pFauxHallway;
		g_pRealHallway = new Framework::Mesh("RealHallway.xml");
		g_pFauxHallway = new Framework::Mesh("FauxHallway.xml");
		break;
	}

	glutPostRedisplay();
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
