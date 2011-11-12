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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

GLuint theProgram;
GLuint positionAttrib;
GLuint colorAttrib;

GLuint modelToCameraMatrixUnif;
GLuint cameraToClipMatrixUnif;
GLuint baseColorUnif;

glm::mat4 cameraToClipMatrix(0.0f);

float CalcFrustumScale(float fFovDeg)
{
	const float degToRad = 3.14159f * 2.0f / 360.0f;
	float fFovRad = fFovDeg * degToRad;
	return 1.0f / tan(fFovRad / 2.0f);
}

const float fFrustumScale = CalcFrustumScale(20.0f);

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "PosColorLocalTransform.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "ColorMultUniform.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	positionAttrib = glGetAttribLocation(theProgram, "position");
	colorAttrib = glGetAttribLocation(theProgram, "color");

	modelToCameraMatrixUnif = glGetUniformLocation(theProgram, "modelToCameraMatrix");
	cameraToClipMatrixUnif = glGetUniformLocation(theProgram, "cameraToClipMatrix");
	baseColorUnif = glGetUniformLocation(theProgram, "baseColor");

	float fzNear = 1.0f; float fzFar = 600.0f;

	cameraToClipMatrix[0].x = fFrustumScale;
	cameraToClipMatrix[1].y = fFrustumScale;
	cameraToClipMatrix[2].z = (fzFar + fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[2].w = -1.0f;
	cameraToClipMatrix[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);
}

enum GimbalAxis
{
	GIMBAL_X_AXIS,
	GIMBAL_Y_AXIS,
	GIMBAL_Z_AXIS,
};

Framework::Mesh *g_Gimbals[3] = {NULL, NULL, NULL};
const char *g_strGimbalNames[3] =
{
	"LargeGimbal.xml",
	"MediumGimbal.xml",
	"SmallGimbal.xml",
};

bool g_bDrawGimbals = true;

void DrawGimbal(glutil::MatrixStack &currMatrix, GimbalAxis eAxis, glm::vec4 baseColor)
{
	if(!g_bDrawGimbals)
		return;

	glutil::PushStack pusher(currMatrix);

	switch(eAxis)
	{
	case GIMBAL_X_AXIS:
		break;
	case GIMBAL_Y_AXIS:
		currMatrix.RotateZ(90.0f);
		currMatrix.RotateX(90.0f);
		break;
	case GIMBAL_Z_AXIS:
		currMatrix.RotateY(90.0f);
		currMatrix.RotateX(90.0f);
		break;
	}

	glUseProgram(theProgram);
	//Set the base color for this object.
	glUniform4fv(baseColorUnif, 1, glm::value_ptr(baseColor));
	glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));

	g_Gimbals[eAxis]->Render();

	glUseProgram(0);
}

Framework::Mesh *g_pObject = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();

	try
	{
		for(int iLoop = 0; iLoop < 3; iLoop++)
		{
			g_Gimbals[iLoop] = new Framework::Mesh(g_strGimbalNames[iLoop]);
		}

		g_pObject = new Framework::Mesh("Ship.xml");
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
}

struct GimbalAngles
{
	GimbalAngles()
		: fAngleX(0.0f)
		, fAngleY(0.0f)
		, fAngleZ(0.0f)
	{}

	float fAngleX;
	float fAngleY;
	float fAngleZ;
};

GimbalAngles g_angles;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutil::MatrixStack currMatrix;
	currMatrix.Translate(glm::vec3(0.0f, 0.0f, -200.0f));
	currMatrix.RotateX(g_angles.fAngleX);
	DrawGimbal(currMatrix, GIMBAL_X_AXIS, glm::vec4(0.4f, 0.4f, 1.0f, 1.0f));
	currMatrix.RotateY(g_angles.fAngleY);
	DrawGimbal(currMatrix, GIMBAL_Y_AXIS, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	currMatrix.RotateZ(g_angles.fAngleZ);
	DrawGimbal(currMatrix, GIMBAL_Z_AXIS, glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));

	glUseProgram(theProgram);
	currMatrix.Scale(3.0, 3.0, 3.0);
	currMatrix.RotateX(-90);
	//Set the base color for this object.
	glUniform4f(baseColorUnif, 1.0, 1.0, 1.0, 1.0);
	glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));

	g_pObject->Render("tint");

	glUseProgram(0);

	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	cameraToClipMatrix[0].x = fFrustumScale * (h / (float)w);
	cameraToClipMatrix[1].y = fFrustumScale;

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

#define STANDARD_ANGLE_INCREMENT 11.25f
#define SMALL_ANGLE_INCREMENT 9.0f

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
		return;
	case 'w': g_angles.fAngleX += SMALL_ANGLE_INCREMENT; break;
	case 's': g_angles.fAngleX -= SMALL_ANGLE_INCREMENT; break;

	case 'a': g_angles.fAngleY += SMALL_ANGLE_INCREMENT; break;
	case 'd': g_angles.fAngleY -= SMALL_ANGLE_INCREMENT; break;

	case 'q': g_angles.fAngleZ += SMALL_ANGLE_INCREMENT; break;
	case 'e': g_angles.fAngleZ -= SMALL_ANGLE_INCREMENT; break;

	case 32:
		g_bDrawGimbals = !g_bDrawGimbals;
		break;
	}

	glutPostRedisplay();
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
