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
#include <glm/gtc/quaternion.hpp>

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

Framework::Mesh *g_pShip = NULL;
Framework::Mesh *g_pPlane = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();

	try
	{
		g_pShip = new Framework::Mesh("Ship.xml");
		g_pPlane = new Framework::Mesh("UnitPlane.xml");
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
static glm::vec3 g_camTarget(0.0f, 10.0f, 0.0f);
static glm::fquat g_orientation(1.0f, 0.0f, 0.0f, 0.0f);

//In spherical coordinates.
static glm::vec3 g_sphereCamRelPos(90.0f, 0.0f, 66.0f);

glm::vec3 ResolveCamPosition()
{
	glutil::MatrixStack tempMat;

	float phi = Framework::DegToRad(g_sphereCamRelPos.x);
	float theta = Framework::DegToRad(g_sphereCamRelPos.y + 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosPhi = cosf(phi);
	float fSinPhi = sinf(phi);

	glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
	return (dirToCamera * g_sphereCamRelPos.z) + g_camTarget;
}

glm::mat4 CalcLookAtMatrix(const glm::vec3 &cameraPt, const glm::vec3 &lookPt, const glm::vec3 &upPt)
{
	glm::vec3 lookDir = glm::normalize(lookPt - cameraPt);
	glm::vec3 upDir = glm::normalize(upPt);

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f);

	rotMat = glm::transpose(rotMat);

	glm::mat4 transMat(1.0f);
	transMat[3] = glm::vec4(-cameraPt, 1.0f);

	return rotMat * transMat;
}


//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutil::MatrixStack currMatrix;
	const glm::vec3 &camPos = ResolveCamPosition();
	currMatrix.SetMatrix(CalcLookAtMatrix(camPos, g_camTarget, glm::vec3(0.0f, 1.0f, 0.0f)));

	glUseProgram(theProgram);

	{
		glutil::PushStack stack(currMatrix);
		currMatrix.Scale(100.0f, 1.0f, 100.0f);

		glUniform4f(baseColorUnif, 0.2f, 0.5f, 0.2f, 1.0f);
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));

		g_pPlane->Render();
	}

	{
		glutil::PushStack stack(currMatrix);
		currMatrix.Translate(g_camTarget);
		currMatrix.ApplyMatrix(glm::mat4_cast(g_orientation));
		currMatrix.RotateX(-90);

		//Set the base color for this object.
		glUniform4f(baseColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(currMatrix.Top()));

		g_pShip->Render("tint");
	}

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

#define SMALL_ANGLE_INCREMENT 9.0f

enum OffsetRelative
{
	MODEL_RELATIVE,
	WORLD_RELATIVE,
	CAMERA_RELATIVE,

	NUM_RELATIVES,
};

static int g_iOffset = MODEL_RELATIVE;

void OffsetOrientation(const glm::vec3 &_axis, float fAngDeg)
{
	float fAngRad = Framework::DegToRad(fAngDeg);

	glm::vec3 axis = glm::normalize(_axis);

	axis = axis * sinf(fAngRad / 2.0f);
	float scalar = cosf(fAngRad / 2.0f);

	glm::fquat offset(scalar, axis.x, axis.y, axis.z);

	switch(g_iOffset)
	{
	case MODEL_RELATIVE:
		g_orientation = g_orientation * offset;
		break;
	case WORLD_RELATIVE:
		g_orientation = offset * g_orientation;
		break;
	case CAMERA_RELATIVE:
		{
			const glm::vec3 &camPos = ResolveCamPosition();
			const glm::mat4 &camMat = CalcLookAtMatrix(camPos, g_camTarget, glm::vec3(0.0f, 1.0f, 0.0f));

			glm::fquat viewQuat = glm::quat_cast(camMat);
			glm::fquat invViewQuat = glm::conjugate(viewQuat);

			const glm::fquat &worldQuat = (invViewQuat * offset * viewQuat);
			g_orientation = worldQuat * g_orientation;
		}
		break;
	}

	g_orientation = glm::normalize(g_orientation);
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
	case 'w': OffsetOrientation(glm::vec3(1.0f, 0.0f, 0.0f), SMALL_ANGLE_INCREMENT); break;
	case 's': OffsetOrientation(glm::vec3(1.0f, 0.0f, 0.0f), -SMALL_ANGLE_INCREMENT); break;

	case 'a': OffsetOrientation(glm::vec3(0.0f, 0.0f, 1.0f), SMALL_ANGLE_INCREMENT); break;
	case 'd': OffsetOrientation(glm::vec3(0.0f, 0.0f, 1.0f), -SMALL_ANGLE_INCREMENT); break;

	case 'q': OffsetOrientation(glm::vec3(0.0f, 1.0f, 0.0f), SMALL_ANGLE_INCREMENT); break;
	case 'e': OffsetOrientation(glm::vec3(0.0f, 1.0f, 0.0f), -SMALL_ANGLE_INCREMENT); break;
	case 32:
		g_iOffset += 1;
		g_iOffset = g_iOffset % NUM_RELATIVES;
		{
			switch(g_iOffset)
			{
			case MODEL_RELATIVE: printf("Model Relative\n"); break;
			case WORLD_RELATIVE: printf("World Relative\n"); break;
			case CAMERA_RELATIVE: printf("Camera Relative\n"); break;
			}
		}
		break;
	case 'i': g_sphereCamRelPos.y -= 11.25f; break;
	case 'k': g_sphereCamRelPos.y += 11.25f; break;
	case 'j': g_sphereCamRelPos.x -= 11.25f; break;
	case 'l': g_sphereCamRelPos.x += 11.25f; break;
	case 'I': g_sphereCamRelPos.y -= 1.125f; break;
	case 'K': g_sphereCamRelPos.y += 1.125f; break;
	case 'J': g_sphereCamRelPos.x -= 1.125f; break;
	case 'L': g_sphereCamRelPos.x += 1.125f; break;
	}

	g_sphereCamRelPos.y = glm::clamp(g_sphereCamRelPos.y, -78.75f, 10.0f);
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
