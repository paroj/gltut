#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <glloader/gl_3_2_comp.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MatrixStack.h"
#include "../framework/MousePole.h"
#include "../framework/ObjectPole.h"
#include "../framework/Timer.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Lights.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;

	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;

	GLuint lightIntensityUnif;
	GLuint ambientIntensityUnif;

	GLuint normalModelToCameraMatrixUnif;
	GLuint cameraSpaceLightPosUnif;
	GLuint lightAttenuationUnif;
	GLuint shininessFactorUnif;
	GLuint baseDiffuseColorUnif;

	void SetWindowData(const glm::mat4 cameraToClip)
	{
		glUseProgram(theProgram);
		glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(cameraToClip));
		glUseProgram(0);
	}
};

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

enum LightingModels
{
	LM_VERT_COLOR_DIFFUSE_SPECULAR = 0,
	LM_VERT_COLOR_DIFFUSE,

	LM_MAX_LIGHTING_MODEL,
};

struct Shaders
{
	const char *fileVertexShader;
	const char *fileFragmentShader;
};

ProgramData g_Programs[LM_MAX_LIGHTING_MODEL];
Shaders g_ShaderFiles[LM_MAX_LIGHTING_MODEL] =
{
	{"PCN.vert", "DiffuseSpecular.frag"},
	{"PCN.vert", "DiffuseOnly.frag"},
};

UnlitProgData g_Unlit;

const int g_iMaterialBlockIndex = 0;
const int g_iLightBlockIndex = 1;
const int g_iProjectionBlockIndex = 2;

UnlitProgData LoadUnlitProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	UnlitProgData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.cameraToClipMatrixUnif = glGetUniformLocation(data.theProgram, "cameraToClipMatrix");
	data.objectColorUnif = glGetUniformLocation(data.theProgram, "objectColor");

	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");
	glUniformBlockBinding(data.theProgram, projectionBlock, g_iProjectionBlockIndex);

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
	data.cameraToClipMatrixUnif = glGetUniformLocation(data.theProgram, "cameraToClipMatrix");

	data.normalModelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "normalModelToCameraMatrix");

	GLuint materialBlock = glGetUniformBlockIndex(data.theProgram, "Material");
	GLuint lightBlock = glGetUniformBlockIndex(data.theProgram, "Light");
	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");

	glUniformBlockBinding(data.theProgram, materialBlock, g_iMaterialBlockIndex);
	glUniformBlockBinding(data.theProgram, lightBlock, g_iLightBlockIndex);
	glUniformBlockBinding(data.theProgram, projectionBlock, g_iProjectionBlockIndex);

	return data;
}

void InitializePrograms()
{
	for(int iProg = 0; iProg < LM_MAX_LIGHTING_MODEL; iProg++)
	{
		g_Programs[iProg] = LoadLitProgram(
			g_ShaderFiles[iProg].fileVertexShader, g_ShaderFiles[iProg].fileFragmentShader);
	}

	g_Unlit = LoadUnlitProgram("PosTransform.vert", "UniformColor.frag");
}

class TimeKeeper
{
public:
	TimeKeeper()
		: keyLightTimer(Framework::Timer::TT_LOOP, 5.0f)
	{}

	void Update()
	{
		keyLightTimer.Update();
	}

	Framework::Timer keyLightTimer;
};

LightManager g_lights;

Framework::RadiusDef radiusDef = {50.0f, 3.0f, 80.0f, 4.0f, 1.0f};
glm::vec3 objectCenter = glm::vec3(-50.0f, 0.0f, 50.0f);

Framework::MousePole g_mousePole(objectCenter, radiusDef);

namespace
{
	void MouseMotion(int x, int y)
	{
		g_mousePole.GLUTMouseMove(glm::ivec2(x, y));
		glutPostRedisplay();
	}

	void MouseButton(int button, int state, int x, int y)
	{
		g_mousePole.GLUTMouseButton(button, state, glm::ivec2(x, y));
		glutPostRedisplay();
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		g_mousePole.GLUTMouseWheel(direction, glm::ivec2(x, y));
		glutPostRedisplay();
	}
}

Framework::Mesh *g_pTerrainMesh = NULL;
Framework::Mesh *g_pLightMesh = NULL;

struct MaterialBlock
{
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	float specularShininess;
	float padding[3];
};

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

GLuint g_lightUniformBuffer;
GLuint g_materialUniformBuffer;
GLuint g_projectionUniformBuffer;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pTerrainMesh = new Framework::Mesh("Ground.xml");
		g_pLightMesh = new Framework::Mesh("UnitCube.xml");
	}
	catch(std::exception &except)
	{
		printf(except.what());
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

	//Setup our Uniform Buffers
	glGenBuffers(1, &g_lightUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBlock), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	MaterialBlock mtlData;
	mtlData.diffuseColor = glm::vec4(1.0f);
	mtlData.specularColor = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
	mtlData.specularShininess = 0.6f;

	glGenBuffers(1, &g_materialUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_materialUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialBlock), &mtlData, GL_STATIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_iLightBlockIndex, g_lightUniformBuffer,
		0, sizeof(LightBlock));

	glBindBufferRange(GL_UNIFORM_BUFFER, g_iProjectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(LightBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

bool g_bDrawCameraPos = false;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	g_lights.UpdateTime();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pLightMesh && g_pLightMesh)
	{
		Framework::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_mousePole.CalcMatrix());

		ProgramData &prog = g_Programs[LM_VERT_COLOR_DIFFUSE_SPECULAR];

		const glm::mat4 &worldToCamMat = modelMatrix.Top();
		LightBlock lightData = g_lights.GetLightPositions(worldToCamMat);

		glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightData), &lightData);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		{
			Framework::MatrixStackPusher push(modelMatrix);

			//Render the ground plane.
			{
				glBindBufferRange(GL_UNIFORM_BUFFER, g_iMaterialBlockIndex, g_materialUniformBuffer,
					0, sizeof(MaterialBlock));

				Framework::MatrixStackPusher push(modelMatrix);
				modelMatrix.RotateX(-90);

				glm::mat3 normMatrix(modelMatrix.Top());
				normMatrix = glm::transpose(glm::inverse(normMatrix));

				glUseProgram(prog.theProgram);
				glUniformMatrix4fv(prog.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glUniformMatrix3fv(prog.normalModelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(normMatrix));
				g_pTerrainMesh->Render();
				glUseProgram(0);

				glBindBufferRange(GL_UNIFORM_BUFFER, g_iMaterialBlockIndex, 0, 0, 0);
			}

			//Render the light
			for(int light = 0; light < g_lights.GetNumberOfPointLights(); light++)
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.Translate(g_lights.GetWorldLightPosition(light));

				glUseProgram(g_Unlit.theProgram);
				glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));
				glUniform4f(g_Unlit.objectColorUnif, 0.8078f, 0.8706f, 0.9922f, 1.0f);
				g_pLightMesh->Render("flat");
			}

			if(g_bDrawCameraPos)
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.SetIdentity();
				modelMatrix.Translate(glm::vec3(0.0f, 0.0f, -g_mousePole.GetLookAtDistance()));

				glDisable(GL_DEPTH_TEST);
				glDepthMask(GL_FALSE);
				glUseProgram(g_Unlit.theProgram);
				glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));
				glUniform4f(g_Unlit.objectColorUnif, 0.25f, 0.25f, 0.25f, 1.0f);
				g_pLightMesh->Render("flat");
				glDepthMask(GL_TRUE);
				glEnable(GL_DEPTH_TEST);
				glUniform4f(g_Unlit.objectColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
				g_pLightMesh->Render("flat");
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
	Framework::MatrixStack persMatrix;
	persMatrix.Perspective(45.0f, (h / (float)w), g_fzNear, g_fzFar);

	ProjectionBlock projData;
	projData.cameraToClipMatrix = persMatrix.Top();

	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ProjectionBlock), &projData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glutPostRedisplay();
}


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
		delete g_pTerrainMesh;
		delete g_pLightMesh;
		glutLeaveMainLoop();
		break;
		
	case 'b': g_lights.TogglePause(); break;
	case 't': g_bDrawCameraPos = !g_bDrawCameraPos; break;

	case 'w': g_mousePole.OffsetTargetPos(Framework::MousePole::DIR_FORWARD, 5.0f); break;
	case 's': g_mousePole.OffsetTargetPos(Framework::MousePole::DIR_BACKWARD, 5.0f); break;
	case 'd': g_mousePole.OffsetTargetPos(Framework::MousePole::DIR_RIGHT, 5.0f); break;
	case 'a': g_mousePole.OffsetTargetPos(Framework::MousePole::DIR_LEFT, 5.0f); break;
	case 'e': g_mousePole.OffsetTargetPos(Framework::MousePole::DIR_UP, 5.0f); break;
	case 'q': g_mousePole.OffsetTargetPos(Framework::MousePole::DIR_DOWN, 5.0f); break;
	}

	glutPostRedisplay();
}


