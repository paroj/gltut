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
#include "../framework/Timer.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;

	GLuint lightIntensityUnif;
	GLuint ambientIntensityUnif;

	GLuint normalModelToCameraMatrixUnif;
	GLuint cameraSpaceLightPosUnif;
	GLuint lightAttenuationUnif;
	GLuint shininessFactorUnif;
	GLuint baseDiffuseColorUnif;
};

struct UnlitProgData
{
	GLuint theProgram;

	GLuint objectColorUnif;
	GLuint modelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_WhiteNoPhong;
ProgramData g_ColorNoPhong;

ProgramData g_WhitePhong;
ProgramData g_ColorPhong;

ProgramData g_WhitePhongOnly;
ProgramData g_ColorPhongOnly;

UnlitProgData g_Unlit;

const int g_projectionBlockIndex = 2;

UnlitProgData LoadUnlitProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	UnlitProgData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.objectColorUnif = glGetUniformLocation(data.theProgram, "objectColor");

	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

ProgramData LoadLitProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.lightIntensityUnif = glGetUniformLocation(data.theProgram, "lightIntensity");
	data.ambientIntensityUnif = glGetUniformLocation(data.theProgram, "ambientIntensity");

	data.normalModelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "normalModelToCameraMatrix");
	data.cameraSpaceLightPosUnif = glGetUniformLocation(data.theProgram, "cameraSpaceLightPos");
	data.lightAttenuationUnif = glGetUniformLocation(data.theProgram, "lightAttenuation");
	data.shininessFactorUnif = glGetUniformLocation(data.theProgram, "shininessFactor");
	data.baseDiffuseColorUnif = glGetUniformLocation(data.theProgram, "baseDiffuseColor");

	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

void InitializePrograms()
{
	g_WhiteNoPhong = LoadLitProgram("PN.vert", "NoPhong.frag");
	g_ColorNoPhong = LoadLitProgram("PCN.vert", "NoPhong.frag");

	g_WhitePhong = LoadLitProgram("PN.vert", "PhongLighting.frag");
	g_ColorPhong = LoadLitProgram("PCN.vert", "PhongLighting.frag");

	g_WhitePhongOnly = LoadLitProgram("PN.vert", "PhongOnly.frag");
	g_ColorPhongOnly = LoadLitProgram("PCN.vert", "PhongOnly.frag");

	g_Unlit = LoadUnlitProgram("PosTransform.vert", "UniformColor.frag");
}

Framework::Mesh *g_pCylinderMesh = NULL;
Framework::Mesh *g_pPlaneMesh = NULL;
Framework::Mesh *g_pCubeMesh = NULL;

///////////////////////////////////////////////
// View/Object Setup
glutil::ViewData g_initialViewData =
{
	glm::vec3(0.0f, 0.5f, 0.0f),
	glm::fquat(0.92387953f, 0.3826834f, 0.0f, 0.0f),
	5.0f,
	0.0f
};

glutil::ViewScale g_viewScale =
{
	3.0f, 20.0f,
	1.5f, 0.5f,
	0.0f, 0.0f,		//No camera movement.
	90.0f/250.0f
};

glutil::ObjectData g_initialObjectData =
{
	glm::vec3(0.0f, 0.5f, 0.0f),
	glm::fquat(1.0f, 0.0f, 0.0f, 0.0f),
};

glutil::ViewPole g_viewPole = glutil::ViewPole(g_initialViewData,
											   g_viewScale, glutil::MB_LEFT_BTN);
glutil::ObjectPole g_objtPole = glutil::ObjectPole(g_initialObjectData,
												   90.0f/250.0f, glutil::MB_RIGHT_BTN, &g_viewPole);

namespace
{
	void MouseMotion(int x, int y)
	{
		Framework::ForwardMouseMotion(g_viewPole, x, y);
		Framework::ForwardMouseMotion(g_objtPole, x, y);
		glutPostRedisplay();
	}

	void MouseButton(int button, int state, int x, int y)
	{
		Framework::ForwardMouseButton(g_viewPole, button, state, x, y);
		Framework::ForwardMouseButton(g_objtPole, button, state, x, y);
		glutPostRedisplay();
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		Framework::ForwardMouseWheel(g_viewPole, wheel, direction, x, y);
		Framework::ForwardMouseWheel(g_objtPole, wheel, direction, x, y);
		glutPostRedisplay();
	}
}

GLuint g_projectionUniformBuffer = 0;

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pCylinderMesh = new Framework::Mesh("UnitCylinder.xml");
		g_pPlaneMesh = new Framework::Mesh("LargePlane.xml");
		g_pCubeMesh = new Framework::Mesh("UnitCube.xml");
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}

 	glutMouseFunc(MouseButton);
 	glutMotionFunc(MouseMotion);
	glutMouseWheelFunc(MouseWheel);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	const float depthZNear = 0.0f;
	const float depthZFar = 1.0f;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(depthZNear, depthZFar);
	glEnable(GL_DEPTH_CLAMP);

	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	//Bind the static buffers.
	glBindBufferRange(GL_UNIFORM_BUFFER, g_projectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static float g_fLightHeight = 1.5f;
static float g_fLightRadius = 1.0f;
using Framework::Timer;
Timer g_LightTimer(Timer::TT_LOOP, 5.0f);

glm::vec4 CalcLightPosition()
{
	float fCurrTimeThroughLoop = g_LightTimer.GetAlpha();

	glm::vec4 ret(0.0f, g_fLightHeight, 0.0f, 1.0f);

	ret.x = cosf(fCurrTimeThroughLoop * (3.14159f * 2.0f)) * g_fLightRadius;
	ret.z = sinf(fCurrTimeThroughLoop * (3.14159f * 2.0f)) * g_fLightRadius;

	return ret;
}

enum LightingModel
{
	LM_PURE_DIFFUSE = 0,
	LM_DIFFUSE_AND_SPECULAR,
	LM_SPECULAR_ONLY,

	LM_MAX_LIGHTING_MODEL,
};

static int g_eLightModel = LM_DIFFUSE_AND_SPECULAR;

static bool g_bUseFragmentLighting = true;
static bool g_bDrawColoredCyl = false;
static bool g_bDrawLightSource = false;
static bool g_bScaleCyl = false;
static bool g_bDrawDark = false;

const float g_fLightAttenuation = 1.2f;
static float g_fShininessFactor = 4.0f;

const glm::vec4 g_darkColor(0.2f, 0.2f, 0.2f, 1.0f);
const glm::vec4 g_lightColor(1.0f);

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.

void display()
{
	g_LightTimer.Update();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pPlaneMesh && g_pCylinderMesh && g_pCubeMesh)
	{
		glutil::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_viewPole.CalcMatrix());

		const glm::vec4 &worldLightPos = CalcLightPosition();
		const glm::vec4 &lightPosCameraSpace = modelMatrix.Top() * worldLightPos;

		ProgramData *pWhiteProg = NULL;
		ProgramData *pColorProg = NULL;

		switch(g_eLightModel)
		{
		case LM_PURE_DIFFUSE:
			pWhiteProg = &g_WhiteNoPhong;
			pColorProg = &g_ColorNoPhong;
			break;
		case LM_DIFFUSE_AND_SPECULAR:
			pWhiteProg = &g_WhitePhong;
			pColorProg = &g_ColorPhong;
			break;
		case LM_SPECULAR_ONLY:
			pWhiteProg = &g_WhitePhongOnly;
			pColorProg = &g_ColorPhongOnly;
			break;
		}

		glUseProgram(pWhiteProg->theProgram);
		glUniform4f(pWhiteProg->lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(pWhiteProg->ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUniform3fv(pWhiteProg->cameraSpaceLightPosUnif,1, glm::value_ptr(lightPosCameraSpace));
		glUniform1f(pWhiteProg->lightAttenuationUnif, g_fLightAttenuation);
		glUniform1f(pWhiteProg->shininessFactorUnif, g_fShininessFactor);
		glUniform4fv(pWhiteProg->baseDiffuseColorUnif, 1,
			g_bDrawDark ? glm::value_ptr(g_darkColor) : glm::value_ptr(g_lightColor));

		glUseProgram(pColorProg->theProgram);
		glUniform4f(pColorProg->lightIntensityUnif, 0.8f, 0.8f, 0.8f, 1.0f);
		glUniform4f(pColorProg->ambientIntensityUnif, 0.2f, 0.2f, 0.2f, 1.0f);
		glUniform3fv(pColorProg->cameraSpaceLightPosUnif, 1, glm::value_ptr(lightPosCameraSpace));
		glUniform1f(pColorProg->lightAttenuationUnif, g_fLightAttenuation);
		glUniform1f(pColorProg->shininessFactorUnif, g_fShininessFactor);
		glUseProgram(0);

		{
			glutil::PushStack push(modelMatrix);

			//Render the ground plane.
			{
				glutil::PushStack push(modelMatrix);

				glm::mat3 normMatrix(modelMatrix.Top());
				normMatrix = glm::transpose(glm::inverse(normMatrix));

				glUseProgram(pWhiteProg->theProgram);
				glUniformMatrix4fv(pWhiteProg->modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glUniformMatrix3fv(pWhiteProg->normalModelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(normMatrix));
				g_pPlaneMesh->Render();
				glUseProgram(0);
			}

			//Render the Cylinder
			{
				glutil::PushStack push(modelMatrix);

				modelMatrix.ApplyMatrix(g_objtPole.CalcMatrix());

				if(g_bScaleCyl)
					modelMatrix.Scale(1.0f, 1.0f, 0.2f);

				glm::mat3 normMatrix(modelMatrix.Top());
				normMatrix = glm::transpose(glm::inverse(normMatrix));

				ProgramData *pProg = g_bDrawColoredCyl ? pColorProg : pWhiteProg;
				glUseProgram(pProg->theProgram);
				glUniformMatrix4fv(pProg->modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glUniformMatrix3fv(pProg->normalModelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(normMatrix));

				if(g_bDrawColoredCyl)
					g_pCylinderMesh->Render("lit-color");
				else
					g_pCylinderMesh->Render("lit");

				glUseProgram(0);
			}

			//Render the light
			if(g_bDrawLightSource)
			{
				glutil::PushStack push(modelMatrix);

				modelMatrix.Translate(glm::vec3(worldLightPos));
				modelMatrix.Scale(0.1f, 0.1f, 0.1f);

				glUseProgram(g_Unlit.theProgram);
				glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));
				glUniform4f(g_Unlit.objectColorUnif, 0.8078f, 0.8706f, 0.9922f, 1.0f);
				g_pCubeMesh->Render("flat");
			}
		}
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glutil::MatrixStack persMatrix;
	persMatrix.Perspective(45.0f, (w / (float)h), g_fzNear, g_fzFar);

	ProjectionBlock projData;
	projData.cameraToClipMatrix = persMatrix.Top();

	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ProjectionBlock), &projData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glutPostRedisplay();
}

static const char *strLightModelNames[] =
{
	"Diffuse only.",
	"Specular + diffuse.",
	"Specular only.",
};


//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	bool bChangedShininess = false;
	bool bChangedLightModel = false;
	switch (key)
	{
	case 27:
		delete g_pPlaneMesh;
		delete g_pCylinderMesh;
		delete g_pCubeMesh;
		glutLeaveMainLoop();
		return;
		
	case 32:
		g_bDrawColoredCyl = !g_bDrawColoredCyl;
		break;

	case 'i': g_fLightHeight += 0.2f; break;
	case 'k': g_fLightHeight -= 0.2f; break;
	case 'l': g_fLightRadius += 0.2f; break;
	case 'j': g_fLightRadius -= 0.2f; break;
	case 'I': g_fLightHeight += 0.05f; break;
	case 'K': g_fLightHeight -= 0.05f; break;
	case 'L': g_fLightRadius += 0.05f; break;
	case 'J': g_fLightRadius -= 0.05f; break;

	case 'o': g_fShininessFactor += 0.5f; bChangedShininess = true; break;
	case 'u': g_fShininessFactor -= 0.5f; bChangedShininess = true; break;
	case 'O': g_fShininessFactor += 0.1f; bChangedShininess = true; break;
	case 'U': g_fShininessFactor -= 0.1f; bChangedShininess = true; break;

	case 'y': g_bDrawLightSource = !g_bDrawLightSource; break;
	case 't': g_bScaleCyl = !g_bScaleCyl; break;
	case 'b': g_LightTimer.TogglePause(); break;
	case 'g': g_bDrawDark = !g_bDrawDark; break;
	case 'h':
		g_eLightModel += 1;
		g_eLightModel %= LM_MAX_LIGHTING_MODEL;
		bChangedLightModel = true;
		break;
	case 'H':
		switch(g_eLightModel)
		{
		case LM_DIFFUSE_AND_SPECULAR:
			g_eLightModel = LM_PURE_DIFFUSE;
			break;
		case LM_PURE_DIFFUSE:
			g_eLightModel = LM_DIFFUSE_AND_SPECULAR;
			break;
		case LM_SPECULAR_ONLY:
			g_eLightModel = LM_PURE_DIFFUSE;
			break;
		}
		bChangedLightModel = true;
		break;
	}

	if(g_fLightRadius < 0.2f)
		g_fLightRadius = 0.2f;

	if(g_fShininessFactor <= 0.0f)
		g_fShininessFactor = 0.0001f;

	if(bChangedShininess)
		printf("Shiny: %f\n", g_fShininessFactor);

	if(bChangedLightModel)
		printf("%s\n", strLightModelNames[g_eLightModel]);

	glutPostRedisplay();
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
