#include <algorithm>
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

#include "Lights.h"
#include "Scene.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct UnlitProgData
{
	GLuint theProgram;

	GLuint objectColorUnif;
	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;

	void SetWindowData(const glm::mat4 cameraToClip)
	{
		glUseProgram(theProgram);
		glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(cameraToClip));
		glUseProgram(0);
	}
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

struct Shaders
{
	const char *fileVertexShader;
	const char *fileFragmentShader;
};

ProgramData g_Programs[LP_MAX_LIGHTING_PROGRAM_TYPES];
Shaders g_ShaderFiles[LP_MAX_LIGHTING_PROGRAM_TYPES] =
{
	{"PCN.vert", "DiffuseSpecularHDR.frag"},
	{"PCN.vert", "DiffuseOnlyHDR.frag"},

	{"PN.vert", "DiffuseSpecularMtlHDR.frag"},
	{"PN.vert", "DiffuseOnlyMtlHDR.frag"},
};

UnlitProgData g_Unlit;

const int g_materialBlockIndex = 0;
const int g_lightBlockIndex = 1;
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

	data.normalModelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "normalModelToCameraMatrix");

	GLuint materialBlock = glGetUniformBlockIndex(data.theProgram, "Material");
	GLuint lightBlock = glGetUniformBlockIndex(data.theProgram, "Light");
	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");

	if(materialBlock != GL_INVALID_INDEX) //Can be optimized out.
		glUniformBlockBinding(data.theProgram, materialBlock, g_materialBlockIndex);
	glUniformBlockBinding(data.theProgram, lightBlock, g_lightBlockIndex);
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

void InitializePrograms()
{
	for(int iProg = 0; iProg < LP_MAX_LIGHTING_PROGRAM_TYPES; iProg++)
	{
		g_Programs[iProg] = LoadLitProgram(
			g_ShaderFiles[iProg].fileVertexShader, g_ShaderFiles[iProg].fileFragmentShader);
	}

	g_Unlit = LoadUnlitProgram("PosTransform.vert", "UniformColor.frag");
}

const ProgramData &GetProgram(LightingProgramTypes eType)
{
	return g_Programs[eType];
}


LightManager g_lights;

///////////////////////////////////////////////
// View/Object Setup
glutil::ViewData g_initialViewData =
{
	glm::vec3(-59.5f, 44.0f, 95.0f),
	glm::fquat(0.92387953f, 0.3826834f, 0.0f, 0.0f),
	50.0f,
	0.0f
};

glutil::ViewScale g_viewScale =
{
	3.0f, 80.0f,
	4.0f, 1.0f,
	5.0f, 1.0f,
	90.0f/250.0f
};

glutil::ViewPole g_viewPole = glutil::ViewPole(g_initialViewData,
											   g_viewScale, glutil::MB_LEFT_BTN);

namespace
{
	void MouseMotion(int x, int y)
	{
		Framework::ForwardMouseMotion(g_viewPole, x, y);
		glutPostRedisplay();
	}

	void MouseButton(int button, int state, int x, int y)
	{
		Framework::ForwardMouseButton(g_viewPole, button, state, x, y);
		glutPostRedisplay();
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		Framework::ForwardMouseWheel(g_viewPole, wheel, direction, x, y);
		glutPostRedisplay();
	}
}

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

GLuint g_lightUniformBuffer;
GLuint g_materialUniformBuffer;
GLuint g_projectionUniformBuffer;

const glm::vec4 g_skyDaylightColor = glm::vec4(0.65f, 0.65f, 1.0f, 1.0f);

void SetupDaytimeLighting()
{
	SunlightValue values[] =
	{
		{ 0.0f/24.0f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), g_skyDaylightColor},
		{ 4.5f/24.0f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), g_skyDaylightColor},
		{ 6.5f/24.0f, glm::vec4(0.15f, 0.05f, 0.05f, 1.0f), glm::vec4(0.3f, 0.1f, 0.10f, 1.0f), glm::vec4(0.5f, 0.1f, 0.1f, 1.0f)},
		{ 8.0f/24.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)},
		{18.0f/24.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)},
		{19.5f/24.0f, glm::vec4(0.15f, 0.05f, 0.05f, 1.0f), glm::vec4(0.3f, 0.1f, 0.1f, 1.0f), glm::vec4(0.5f, 0.1f, 0.1f, 1.0f)},
		{20.5f/24.0f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), g_skyDaylightColor},
	};

	g_lights.SetSunlightValues(values, 7);

	g_lights.SetPointLightIntensity(0, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	g_lights.SetPointLightIntensity(1, glm::vec4(0.0f, 0.0f, 0.3f, 1.0f));
	g_lights.SetPointLightIntensity(2, glm::vec4(0.3f, 0.0f, 0.0f, 1.0f));
}

void SetupNighttimeLighting()
{
	SunlightValue values[] =
	{
		{ 0.0f/24.0f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), g_skyDaylightColor},
		{ 4.5f/24.0f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), g_skyDaylightColor},
		{ 6.5f/24.0f, glm::vec4(0.15f, 0.05f, 0.05f, 1.0f), glm::vec4(0.3f, 0.1f, 0.10f, 1.0f), glm::vec4(0.5f, 0.1f, 0.1f, 1.0f)},
		{ 8.0f/24.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)},
		{18.0f/24.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)},
		{19.5f/24.0f, glm::vec4(0.15f, 0.05f, 0.05f, 1.0f), glm::vec4(0.3f, 0.1f, 0.1f, 1.0f), glm::vec4(0.5f, 0.1f, 0.1f, 1.0f)},
		{20.5f/24.0f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), g_skyDaylightColor},
	};

	g_lights.SetSunlightValues(values, 7);

	g_lights.SetPointLightIntensity(0, glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
	g_lights.SetPointLightIntensity(1, glm::vec4(0.0f, 0.0f, 0.7f, 1.0f));
	g_lights.SetPointLightIntensity(2, glm::vec4(0.7f, 0.0f, 0.0f, 1.0f));
}

void SetupHDRLighting()
{
	SunlightValueHDR values[] =
	{
		{ 0.0f/24.0f, glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), glm::vec4(1.8f, 1.8f, 1.8f, 1.0f), g_skyDaylightColor, 3.0f},
		{ 4.5f/24.0f, glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), glm::vec4(1.8f, 1.8f, 1.8f, 1.0f), g_skyDaylightColor, 3.0f},
		{ 6.5f/24.0f, glm::vec4(0.225f, 0.075f, 0.075f, 1.0f), glm::vec4(0.45f, 0.15f, 0.15f, 1.0f), glm::vec4(0.5f, 0.1f, 0.1f, 1.0f), 1.5f},
		{ 8.0f/24.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f},
		{18.0f/24.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f},
		{19.5f/24.0f, glm::vec4(0.225f, 0.075f, 0.075f, 1.0f), glm::vec4(0.45f, 0.15f, 0.15f, 1.0f), glm::vec4(0.5f, 0.1f, 0.1f, 1.0f), 1.5f},
		{20.5f/24.0f, glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), glm::vec4(1.8f, 1.8f, 1.8f, 1.0f), g_skyDaylightColor, 3.0f},
	};

	g_lights.SetSunlightValues(values, 7);

	g_lights.SetPointLightIntensity(0, glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
	g_lights.SetPointLightIntensity(1, glm::vec4(0.0f, 0.0f, 0.7f, 1.0f));
	g_lights.SetPointLightIntensity(2, glm::vec4(0.7f, 0.0f, 0.0f, 1.0f));
}

Scene *g_pScene = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pScene = new Scene();
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}

	SetupDaytimeLighting();

	g_lights.CreateTimer("tetra", Framework::Timer::TT_LOOP, 2.5f);

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

	//Setup our Uniform Buffers
	glGenBuffers(1, &g_lightUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBlock), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	//Bind the static buffers.
	glBindBufferRange(GL_UNIFORM_BUFFER, g_lightBlockIndex, g_lightUniformBuffer,
		0, sizeof(LightBlock));

	glBindBufferRange(GL_UNIFORM_BUFFER, g_projectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

bool g_bDrawCameraPos = false;
bool g_bDrawLights = true;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	g_lights.UpdateTime();

	glm::vec4 bkg = g_lights.GetBackgroundColor();

	glClearColor(bkg[0], bkg[1], bkg[2], bkg[3]);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutil::MatrixStack modelMatrix;
	modelMatrix.SetMatrix(g_viewPole.CalcMatrix());

	const glm::mat4 &worldToCamMat = modelMatrix.Top();
	LightBlockHDR lightData = g_lights.GetLightInformationHDR(worldToCamMat);

	glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightData), &lightData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	if(g_pScene)
	{
		glutil::PushStack push(modelMatrix);

		g_pScene->Draw(modelMatrix, g_materialBlockIndex, g_lights.GetTimerValue("tetra"));
	}

	{
		glutil::PushStack push(modelMatrix);
		//Render the sun
		{
			glutil::PushStack push(modelMatrix);

			glm::vec3 sunlightDir(g_lights.GetSunlightDirection());
			modelMatrix.Translate(sunlightDir * 500.0f);
			modelMatrix.Scale(30.0f, 30.0f, 30.0f);

			glUseProgram(g_Unlit.theProgram);
			glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));

			glm::vec4 lightColor = g_lights.GetSunlightIntensity();
			glUniform4fv(g_Unlit.objectColorUnif, 1, glm::value_ptr(lightColor));
			g_pScene->GetSphereMesh()->Render("flat");
		}

		//Render the lights
		if(g_bDrawLights)
		{
			for(int light = 0; light < g_lights.GetNumberOfPointLights(); light++)
			{
				glutil::PushStack push(modelMatrix);

				modelMatrix.Translate(g_lights.GetWorldLightPosition(light));

				glUseProgram(g_Unlit.theProgram);
				glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glm::vec4 lightColor = g_lights.GetPointLightIntensity(light);
				glUniform4fv(g_Unlit.objectColorUnif, 1, glm::value_ptr(lightColor));
				g_pScene->GetCubeMesh()->Render("flat");
			}
		}

		if(g_bDrawCameraPos)
		{
			glutil::PushStack push(modelMatrix);

			modelMatrix.SetIdentity();
			modelMatrix.Translate(glm::vec3(0.0f, 0.0f, -g_viewPole.GetView().radius));

			glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
			glUseProgram(g_Unlit.theProgram);
			glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));
			glUniform4f(g_Unlit.objectColorUnif, 0.25f, 0.25f, 0.25f, 1.0f);
			g_pScene->GetCubeMesh()->Render("flat");
			glDepthMask(GL_TRUE);
			glEnable(GL_DEPTH_TEST);
			glUniform4f(g_Unlit.objectColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
			g_pScene->GetCubeMesh()->Render("flat");
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


TimerTypes g_eTimerMode = TIMER_ALL;

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
		delete g_pScene;
		g_pScene = NULL;
		glutLeaveMainLoop();
		return;
		
	case 'p': g_lights.TogglePause(g_eTimerMode); break;
	case '-': g_lights.RewindTime(g_eTimerMode, 1.0f); break;
	case '=': g_lights.FastForwardTime(g_eTimerMode, 1.0f); break;
	case 't': g_bDrawCameraPos = !g_bDrawCameraPos; break;
	case '1': g_eTimerMode = TIMER_ALL; printf("All\n"); break;
	case '2': g_eTimerMode = TIMER_SUN; printf("Sun\n"); break;
	case '3': g_eTimerMode = TIMER_LIGHTS; printf("Lights\n"); break;

	case 'l': SetupDaytimeLighting(); break;
	case 'L': SetupNighttimeLighting(); break;
	case 'k': SetupHDRLighting(); break;

	case 32:
		{
			float sunAlpha = g_lights.GetSunTime();
			float sunTimeHours = sunAlpha * 24.0f + 12.0f;
			sunTimeHours = sunTimeHours > 24.0f ? sunTimeHours - 24.0f : sunTimeHours;
			int sunHours = int(sunTimeHours);
			float sunTimeMinutes = (sunTimeHours - sunHours) * 60.0f;
			int sunMinutes = int(sunTimeMinutes);
			printf("%02i:%02i\n", sunHours, sunMinutes);
		}
		break;
	}

	g_viewPole.CharPress(key);
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
