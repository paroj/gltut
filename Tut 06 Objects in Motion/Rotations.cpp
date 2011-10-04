#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

GLuint theProgram;

GLuint modelToCameraMatrixUnif;
GLuint cameraToClipMatrixUnif;

glm::mat4 cameraToClipMatrix(0.0f);

float CalcFrustumScale(float fFovDeg)
{
	const float degToRad = 3.14159f * 2.0f / 360.0f;
	float fFovRad = fFovDeg * degToRad;
	return 1.0f / tan(fFovRad / 2.0f);
}

const float fFrustumScale = CalcFrustumScale(45.0f);

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "PosColorLocalTransform.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "ColorPassthrough.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	modelToCameraMatrixUnif = glGetUniformLocation(theProgram, "modelToCameraMatrix");
	cameraToClipMatrixUnif = glGetUniformLocation(theProgram, "cameraToClipMatrix");

	float fzNear = 1.0f; float fzFar = 61.0f;

	cameraToClipMatrix[0].x = fFrustumScale;
	cameraToClipMatrix[1].y = fFrustumScale;
	cameraToClipMatrix[2].z = (fzFar + fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[2].w = -1.0f;
	cameraToClipMatrix[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);
}

const int numberOfVertices = 8;

#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertexData[] =
{
	+1.0f, +1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,
};

const GLshort indexData[] =
{
	0, 1, 2,
	1, 0, 3,
	2, 3, 0,
	3, 2, 1,

	5, 4, 6,
	4, 5, 7,
	7, 6, 4,
	6, 7, 5,
};

GLuint vertexBufferObject;
GLuint indexBufferObject;
GLuint vao;


void InitializeVertexBuffer()
{
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

float CalcLerpFactor(float fElapsedTime, float fLoopDuration)
{
	float fValue = fmodf(fElapsedTime, fLoopDuration) / fLoopDuration;
	if(fValue > 0.5f)
		fValue = 1.0f - fValue;

	return fValue * 2.0f;
}

glm::mat3 NullRotation(float fElapsedTime)
{
	return glm::mat3(1.0f);
}

float ComputeAngleRad(float fElapsedTime, float fLoopDuration)
{
	const float fScale = 3.14159f * 2.0f / fLoopDuration;
	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
	return fCurrTimeThroughLoop * fScale;
}

glm::mat3 RotateX(float fElapsedTime)
{
	float fAngRad = ComputeAngleRad(fElapsedTime, 3.0);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[1].y = fCos; theMat[2].y = -fSin;
	theMat[1].z = fSin; theMat[2].z = fCos;
	return theMat;
}

glm::mat3 RotateY(float fElapsedTime)
{
	float fAngRad = ComputeAngleRad(fElapsedTime, 2.0);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[0].x = fCos; theMat[2].x = fSin;
	theMat[0].z = -fSin; theMat[2].z = fCos;
	return theMat;
}

glm::mat3 RotateZ(float fElapsedTime)
{
	float fAngRad = ComputeAngleRad(fElapsedTime, 2.0);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[0].x = fCos; theMat[1].x = -fSin;
	theMat[0].y = fSin; theMat[1].y = fCos;
	return theMat;
}

glm::mat3 RotateAxis(float fElapsedTime)
{
	float fAngRad = ComputeAngleRad(fElapsedTime, 2.0);
	float fCos = cosf(fAngRad);
	float fInvCos = 1.0f - fCos;
	float fSin = sinf(fAngRad);
	float fInvSin = 1.0f - fSin;

	glm::vec3 axis(1.0f, 1.0f, 1.0f);
	axis = glm::normalize(axis);

	glm::mat3 theMat(1.0f);
	theMat[0].x = (axis.x * axis.x) + ((1 - axis.x * axis.x) * fCos);
	theMat[1].x = axis.x * axis.y * (fInvCos) - (axis.z * fSin);
	theMat[2].x = axis.x * axis.z * (fInvCos) + (axis.y * fSin);

	theMat[0].y = axis.x * axis.y * (fInvCos) + (axis.z * fSin);
	theMat[1].y = (axis.y * axis.y) + ((1 - axis.y * axis.y) * fCos);
	theMat[2].y = axis.y * axis.z * (fInvCos) - (axis.x * fSin);

	theMat[0].z = axis.x * axis.z * (fInvCos) - (axis.y * fSin);
	theMat[1].z = axis.y * axis.z * (fInvCos) + (axis.x * fSin);
	theMat[2].z = (axis.z * axis.z) + ((1 - axis.z * axis.z) * fCos);
	return theMat;
}

glm::vec3 DynamicNonUniformScale(float fElapsedTime)
{
	const float fXLoopDuration = 3.0f;
	const float fZLoopDuration = 5.0f;

	return glm::vec3(glm::mix(1.0f, 0.5f, CalcLerpFactor(fElapsedTime, fXLoopDuration)),
		1.0f,
		glm::mix(1.0f, 10.0f, CalcLerpFactor(fElapsedTime, fZLoopDuration)));
}

struct Instance
{
	typedef glm::mat3(*RotationFunc)(float);

	RotationFunc CalcRotation;
	glm::vec3 offset;

	glm::mat4 ConstructMatrix(float fElapsedTime)
	{
		const glm::mat3 &rotMatrix = CalcRotation(fElapsedTime);
		glm::mat4 theMat(rotMatrix);
		theMat[3] = glm::vec4(offset, 1.0f);

		return theMat;
	}
};

Instance g_instanceList[] =
{
	{NullRotation,				glm::vec3(0.0f, 0.0f, -25.0f)},
	{RotateX,					glm::vec3(-5.0f, -5.0f, -25.0f)},
	{RotateY,					glm::vec3(-5.0f, 5.0f, -25.0f)},
	{RotateZ,					glm::vec3(5.0f, 5.0f, -25.0f)},
	{RotateAxis,				glm::vec3(5.0f, -5.0f, -25.0f)},
};

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(theProgram);

	glBindVertexArray(vao);

	float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	for(int iLoop = 0; iLoop < ARRAY_COUNT(g_instanceList); iLoop++)
	{
		Instance &currInst = g_instanceList[iLoop];
		const glm::mat4 &transformMatrix = currInst.ConstructMatrix(fElapsedTime);

		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
	}

	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();
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
	}
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
