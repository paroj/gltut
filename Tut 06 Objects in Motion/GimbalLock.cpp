#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <glloader/gl_3_2_comp.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
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

const float fFrustumScale = CalcFrustumScale(45.0f);

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

	float fzNear = 1.0f; float fzFar = 100.0f;

	cameraToClipMatrix[0].x = fFrustumScale;
	cameraToClipMatrix[1].y = fFrustumScale;
	cameraToClipMatrix[2].z = (fzFar + fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[2].w = -1.0f;
	cameraToClipMatrix[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);
}

const int numberOfVertices = 24;

#define FULL_COLOR 1.0f, 1.0f, 1.0f, 1.0f
#define LIGHT_COLOR 0.75f, 0.75f, 0.75f, 1.0f
#define MID_COLOR 0.5f, 0.5f, 0.5f, 1.0f
#define DARK_COLOR 	0.3f, 0.3f, 0.3f, 1.0f


const float vertexData[] =
{
	//Front
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,

	//Top
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f,

	//Left
	+0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f,

	//Back
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,

	//Bottom
	+0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,

	//Right
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f,


	FULL_COLOR,
	FULL_COLOR,
	FULL_COLOR,
	FULL_COLOR,

	LIGHT_COLOR,
	LIGHT_COLOR,
	LIGHT_COLOR,
	LIGHT_COLOR,

	MID_COLOR,
	MID_COLOR,
	MID_COLOR,
	MID_COLOR,

	FULL_COLOR,
	FULL_COLOR,
	FULL_COLOR,
	FULL_COLOR,

	LIGHT_COLOR,
	LIGHT_COLOR,
	LIGHT_COLOR,
	LIGHT_COLOR,

	MID_COLOR,
	MID_COLOR,
	MID_COLOR,
	MID_COLOR,
};

const GLshort indexData[] =
{
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8,

	12, 13, 14,
	14, 15, 12,

	16, 17, 18,
	18, 19, 16,

	20, 21, 22,
	22, 23, 20,
};

GLuint vertexBufferObject;
GLuint indexBufferObject;
GLuint vao;

void InitializeVAO()
{
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(positionAttrib);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);
}

inline float DegToRad(float fAngDeg)
{
	const float fDegToRad = 3.14159f * 2.0f / 360.0f;
	return fAngDeg * fDegToRad;
}

inline float Clamp(float fValue, float fMinValue, float fMaxValue)
{
	if(fValue < fMinValue)
		return fMinValue;

	if(fValue > fMaxValue)
		return fMaxValue;

	return fValue;
}

glm::mat3 RotateX(float fAngDeg)
{
	float fAngRad = DegToRad(fAngDeg);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[1].y = fCos; theMat[2].y = -fSin;
	theMat[1].z = fSin; theMat[2].z = fCos;
	return theMat;
}

glm::mat3 RotateY(float fAngDeg)
{
	float fAngRad = DegToRad(fAngDeg);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[0].x = fCos; theMat[2].x = fSin;
	theMat[0].z = -fSin; theMat[2].z = fCos;
	return theMat;
}

glm::mat3 RotateZ(float fAngDeg)
{
	float fAngRad = DegToRad(fAngDeg);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[0].x = fCos; theMat[1].x = -fSin;
	theMat[0].y = fSin; theMat[1].y = fCos;
	return theMat;
}

class MatrixStack
{
public:
	MatrixStack()
		: m_currMat(1.0f)
	{
	}

	const glm::mat4 &Top()
	{
		return m_currMat;
	}

	void RotateX(float fAngDeg)
	{
		m_currMat = m_currMat * glm::mat4(::RotateX(fAngDeg));
	}

	void RotateY(float fAngDeg)
	{
		m_currMat = m_currMat * glm::mat4(::RotateY(fAngDeg));
	}

	void RotateZ(float fAngDeg)
	{
		m_currMat = m_currMat * glm::mat4(::RotateZ(fAngDeg));
	}

	void Scale(const glm::vec3 &scaleVec)
	{
		glm::mat4 scaleMat(1.0f);
		scaleMat[0].x = scaleVec.x;
		scaleMat[1].y = scaleVec.y;
		scaleMat[2].z = scaleVec.z;

		m_currMat = m_currMat * scaleMat;
	}

	void Translate(const glm::vec3 &offsetVec)
	{
		glm::mat4 translateMat(1.0f);
		translateMat[3] = glm::vec4(offsetVec, 1.0f);

		m_currMat = m_currMat * translateMat;
	}

	void Push()
	{
		m_matrices.push(m_currMat);
	}

	void Pop()
	{
		m_currMat = m_matrices.top();
		m_matrices.pop();
	}

private:
	glm::mat4 m_currMat;
	std::stack<glm::mat4> m_matrices;
};

void DrawGimbalSides(MatrixStack &currMatrix, float fGimbolSidesOffset, float fGimbolSidesScale)
{
	//Draw the top
	{
		currMatrix.Push();
		currMatrix.Translate(glm::vec3(0.0f, fGimbolSidesOffset, 0.0f));
		currMatrix.Scale(glm::vec3(fGimbolSidesScale, 1.0f, 1.0f));
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
		currMatrix.Pop();
	}

	//Draw the bottom
	{
		currMatrix.Push();
		currMatrix.Translate(glm::vec3(0.0f, -fGimbolSidesOffset, 0.0f));
		currMatrix.Scale(glm::vec3(fGimbolSidesScale, 1.0f, 1.0f));
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
		currMatrix.Pop();
	}

	//Draw the right
	{
		currMatrix.Push();
		currMatrix.Translate(glm::vec3(fGimbolSidesOffset, 0.0f, 0.0f));
		currMatrix.Scale(glm::vec3(1.0f, fGimbolSidesScale, 1.0f));
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
		currMatrix.Pop();
	}

	//Draw the left
	{
		currMatrix.Push();
		currMatrix.Translate(glm::vec3(-fGimbolSidesOffset, 0.0f, 0.0f));
		currMatrix.Scale(glm::vec3(1.0f, fGimbolSidesScale, 1.0f));
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
		currMatrix.Pop();
	}
}

void DrawGimbalAttachments(MatrixStack &currMatrix, float fGimbalAttachOffset)
{
	//Draw the right attachment.
	{
		currMatrix.Push();
		currMatrix.Translate(glm::vec3(fGimbalAttachOffset, 0.0f, 0.0f));
		currMatrix.Scale(glm::vec3(1.0f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
		currMatrix.Pop();
	}

	//Draw the left attachment.
	{
		currMatrix.Push();
		currMatrix.Translate(glm::vec3(-fGimbalAttachOffset, 0.0f, 0.0f));
		currMatrix.Scale(glm::vec3(1.0f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
		currMatrix.Pop();
	}
}


void DrawBaseGimbal(MatrixStack &currMatrix, float fSize, glm::vec4 baseColor)
{
	//A Gimbal can only be 4 units in size or more.
	assert(fSize > 4.0f);

	glUseProgram(theProgram);
	//Set the base color for this object.
	glUniform4fv(baseColorUnif, 1, glm::value_ptr(baseColor));
	glBindVertexArray(vao);

	float fGimbolSidesOffset = (fSize / 2.0f) - 1.5f;
	float fGimbolSidesScale = fSize - 2.0f;

	DrawGimbalSides(currMatrix, fGimbolSidesOffset, fGimbolSidesScale);
	
	float fGimbalAttachOffset = (fSize / 2.0f) - 0.5f;

	DrawGimbalAttachments(currMatrix, fGimbalAttachOffset);

	glBindVertexArray(0);
	glUseProgram(0);
}

enum GimbalAxis
{
	GIMBAL_X_AXIS,
	GIMBAL_Y_AXIS,
	GIMBAL_Z_AXIS,
};

void DrawGimbal(MatrixStack &currMatrix, GimbalAxis eAxis, float fSize, glm::vec4 baseColor)
{
	currMatrix.Push();

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

	DrawBaseGimbal(currMatrix, fSize, baseColor);
	currMatrix.Pop();
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	InitializeVAO();


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

	MatrixStack currMatrix;
	currMatrix.Translate(glm::vec3(0.0f, 0.0f, -60.0f));
	currMatrix.RotateX(g_angles.fAngleX);
	DrawGimbal(currMatrix, GIMBAL_X_AXIS, 30.0f, glm::vec4(0.4f, 0.4f, 1.0f, 1.0f));
	currMatrix.RotateY(g_angles.fAngleY);
	DrawGimbal(currMatrix, GIMBAL_Y_AXIS, 26.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	currMatrix.RotateZ(g_angles.fAngleZ);
	DrawGimbal(currMatrix, GIMBAL_Z_AXIS, 22.0f, glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));

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
		break;
	case 'w': g_angles.fAngleX += SMALL_ANGLE_INCREMENT; break;
	case 's': g_angles.fAngleX -= SMALL_ANGLE_INCREMENT; break;

	case 'a': g_angles.fAngleY += SMALL_ANGLE_INCREMENT; break;
	case 'd': g_angles.fAngleY -= SMALL_ANGLE_INCREMENT; break;

	case 'q': g_angles.fAngleZ += SMALL_ANGLE_INCREMENT; break;
	case 'e': g_angles.fAngleZ -= SMALL_ANGLE_INCREMENT; break;
	}
}


