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
#include "../framework/UniformBlockArray.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramMeshData
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;
	GLuint normalModelToCameraMatrixUnif;
};

struct ProgramImposData
{
	GLuint theProgram;

	GLuint sphereRadiusUnif;
	GLuint cameraSpherePosUnif;
};

struct UnlitProgData
{
	GLuint theProgram;

	GLuint objectColorUnif;
	GLuint modelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

enum Impostors
{
	IMP_BASIC,
 	IMP_PERSPECTIVE,
 	IMP_DEPTH,

	IMP_NUM_IMPOSTORS,
};

ProgramMeshData g_litMeshProg;
ProgramImposData g_litImpProgs[IMP_NUM_IMPOSTORS];
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

ProgramMeshData LoadLitMeshProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramMeshData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");

	data.normalModelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "normalModelToCameraMatrix");

	GLuint materialBlock = glGetUniformBlockIndex(data.theProgram, "Material");
	GLuint lightBlock = glGetUniformBlockIndex(data.theProgram, "Light");
	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");

	glUniformBlockBinding(data.theProgram, materialBlock, g_materialBlockIndex);
	glUniformBlockBinding(data.theProgram, lightBlock, g_lightBlockIndex);
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

ProgramImposData LoadLitImposProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramImposData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.sphereRadiusUnif = glGetUniformLocation(data.theProgram, "sphereRadius");
	data.cameraSpherePosUnif = glGetUniformLocation(data.theProgram, "cameraSpherePos");

	GLuint materialBlock = glGetUniformBlockIndex(data.theProgram, "Material");
	GLuint lightBlock = glGetUniformBlockIndex(data.theProgram, "Light");
	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");

	glUniformBlockBinding(data.theProgram, materialBlock, g_materialBlockIndex);
	glUniformBlockBinding(data.theProgram, lightBlock, g_lightBlockIndex);
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

const char *g_impShaderNames[IMP_NUM_IMPOSTORS * 2] =
{
	"BasicImpostor.vert", "BasicImpostor.frag",
 	"PerspImpostor.vert", "PerspImpostor.frag",
 	"DepthImpostor.vert", "DepthImpostor.frag",
};

void InitializePrograms()
{
	g_litMeshProg = LoadLitMeshProgram("PN.vert", "Lighting.frag");

	for(int iLoop = 0; iLoop < IMP_NUM_IMPOSTORS; iLoop++)
	{
		g_litImpProgs[iLoop] = LoadLitImposProgram(
			g_impShaderNames[iLoop * 2], g_impShaderNames[iLoop * 2 + 1]);
	}

	g_Unlit = LoadUnlitProgram("Unlit.vert", "Unlit.frag");
}

///////////////////////////////////////////////
// View/Object Setup
glutil::ViewData g_initialViewData =
{
	glm::vec3(0.0f, 30.0f, 25.0f),
	glm::fquat(0.92387953f, 0.3826834f, 0.0f, 0.0f),
	10.0f,
	0.0f
};

glutil::ViewScale g_viewScale =
{
	3.0f, 70.0f,
	3.5f, 1.5f,
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

struct PerLight
{
	glm::vec4 cameraSpaceLightPos;
	glm::vec4 lightIntensity;
};

const int NUMBER_OF_LIGHTS = 2;

struct LightBlock
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float padding[3];
	PerLight lights[NUMBER_OF_LIGHTS];
};

struct MaterialBlock
{
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	float specularShininess;
	float padding[3];
};

Framework::Mesh *g_pPlaneMesh = NULL;
Framework::Mesh *g_pSphereMesh = NULL;
Framework::Mesh *g_pCubeMesh = NULL;

GLuint g_lightUniformBuffer = 0;
GLuint g_projectionUniformBuffer = 0;
GLuint g_materialUniformBuffer = 0;

int g_materialBlockOffset = 0;

enum MaterialNames
{
	MTL_TERRAIN = 0,
	MTL_BLUE_SHINY,
	MTL_GOLD_METAL,
	MTL_DULL_GREY,
	MTL_BLACK_SHINY,

	NUM_MATERIALS,
};

void CreateMaterials()
{
	Framework::UniformBlockArray<MaterialBlock, NUM_MATERIALS> ubArray;
	g_materialBlockOffset = ubArray.GetArrayOffset();

	MaterialBlock mtl;
	mtl.diffuseColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.specularColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.specularShininess = 0.6f;
	ubArray[MTL_TERRAIN] = mtl;

	mtl.diffuseColor = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f);
	mtl.specularColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	mtl.specularShininess = 0.1f;
	ubArray[MTL_BLUE_SHINY] = mtl;

	mtl.diffuseColor = glm::vec4(0.803f, 0.709f, 0.15f, 1.0f);
	mtl.specularColor = glm::vec4(0.803f, 0.709f, 0.15f, 1.0f) * 0.75;
	mtl.specularShininess = 0.18f;
	ubArray[MTL_GOLD_METAL] = mtl;

	mtl.diffuseColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	mtl.specularColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	mtl.specularShininess = 0.8f;
	ubArray[MTL_DULL_GREY] = mtl;

	mtl.diffuseColor = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
	mtl.specularColor = glm::vec4(0.95f, 0.95f, 0.95f, 1.0f);
	mtl.specularShininess = 0.3f;
	ubArray[MTL_BLACK_SHINY] = mtl;

	g_materialUniformBuffer = ubArray.CreateBufferObject();
}

GLuint g_imposterVAO;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pPlaneMesh = new Framework::Mesh("LargePlane.xml");
		g_pSphereMesh = new Framework::Mesh("UnitSphere.xml");
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

	//Empty Vertex Array Object.
	glGenVertexArrays(1, &g_imposterVAO);

	CreateMaterials();
}

int g_currImpostor = IMP_BASIC;

void DrawSphere(glutil::MatrixStack &modelMatrix,
				const glm::vec3 &position, float radius, MaterialNames material,
				bool bDrawImposter = false)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, g_materialUniformBuffer,
		material * g_materialBlockOffset, sizeof(MaterialBlock));

	if(bDrawImposter)
	{
		glm::vec4 cameraSpherePos = modelMatrix.Top() * glm::vec4(position, 1.0f);
		glUseProgram(g_litImpProgs[g_currImpostor].theProgram);
		glUniform3fv(g_litImpProgs[g_currImpostor].cameraSpherePosUnif, 1, glm::value_ptr(cameraSpherePos));
		glUniform1f(g_litImpProgs[g_currImpostor].sphereRadiusUnif, radius);

		glBindVertexArray(g_imposterVAO);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBindVertexArray(0);
		glUseProgram(0);
	}
	else
	{
		glutil::PushStack push(modelMatrix);
		modelMatrix.Translate(position);
		modelMatrix.Scale(radius * 2.0f); //The unit sphere has a radius 0.5f.

		glm::mat3 normMatrix(modelMatrix.Top());
		normMatrix = glm::transpose(glm::inverse(normMatrix));

		glUseProgram(g_litMeshProg.theProgram);
		glUniformMatrix4fv(g_litMeshProg.modelToCameraMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(modelMatrix.Top()));
		glUniformMatrix3fv(g_litMeshProg.normalModelToCameraMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(normMatrix));

		g_pSphereMesh->Render("lit");

		glUseProgram(0);
	}

	glBindBufferBase(GL_UNIFORM_BUFFER, g_materialBlockIndex, 0);
}

void DrawSphereOrbit(glutil::MatrixStack &modelMatrix,
					 const glm::vec3 &orbitCenter, const glm::vec3 &orbitAxis,
					 float orbitRadius, float orbitAlpha, float sphereRadius, MaterialNames material,
					 bool drawImposter = false)
{
	glutil::PushStack push(modelMatrix);

	modelMatrix.Translate(orbitCenter);
	modelMatrix.Rotate(orbitAxis, 360.0f * orbitAlpha);

	glm::vec3 offsetDir = glm::cross(orbitAxis, glm::vec3(0.0f, 1.0f, 0.0f));
	if(glm::length(offsetDir) < 0.001f)
		offsetDir = glm::cross(orbitAxis, glm::vec3(1.0f, 0.0f, 0.0f));

	offsetDir = glm::normalize(offsetDir);

	modelMatrix.Translate(offsetDir * orbitRadius);

	DrawSphere(modelMatrix, glm::vec3(0.0f), sphereRadius, material, drawImposter);
}

bool g_bDrawCameraPos = false;
bool g_bDrawLights = true;

Framework::Timer g_sphereTimer(Framework::Timer::TT_LOOP, 6.0f);

float g_lightHeight = 20.0f;

glm::vec4 CalcLightPosition()
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f;

	float timeThroughLoop = g_sphereTimer.GetAlpha();

	glm::vec4 ret(0.0f, g_lightHeight, 0.0f, 1.0f);

	ret.x = cosf(timeThroughLoop * fScale) * 20.0f;
	ret.z = sinf(timeThroughLoop * fScale) * 20.0f;

	return ret;
}

const float g_fHalfLightDistance = 25.0f;
const float g_fLightAttenuation = 1.0f / (g_fHalfLightDistance * g_fHalfLightDistance);

bool g_drawImposter[4] = { false, false, false, false };

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	g_sphereTimer.Update();

	glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pPlaneMesh && g_pSphereMesh && g_pCubeMesh)
	{
		glutil::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_viewPole.CalcMatrix());
		const glm::mat4 &worldToCamMat = modelMatrix.Top();

		LightBlock lightData;

		lightData.ambientIntensity = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		lightData.lightAttenuation = g_fLightAttenuation;

		lightData.lights[0].cameraSpaceLightPos = worldToCamMat * glm::vec4(0.707f, 0.707f, 0.0f, 0.0f);
		lightData.lights[0].lightIntensity = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);

		lightData.lights[1].cameraSpaceLightPos = worldToCamMat * CalcLightPosition();
		lightData.lights[1].lightIntensity = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);

		glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightData), &lightData);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		{
			glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, g_materialUniformBuffer,
				MTL_TERRAIN * g_materialBlockOffset, sizeof(MaterialBlock));

			glm::mat3 normMatrix(modelMatrix.Top());
			normMatrix = glm::transpose(glm::inverse(normMatrix));

			glUseProgram(g_litMeshProg.theProgram);
			glUniformMatrix4fv(g_litMeshProg.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));
			glUniformMatrix3fv(g_litMeshProg.normalModelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(normMatrix));

			g_pPlaneMesh->Render();

			glUseProgram(0);
			glBindBufferBase(GL_UNIFORM_BUFFER, g_materialBlockIndex, 0);
		}

		DrawSphere(modelMatrix, glm::vec3(0.0f, 10.0f, 0.0f), 4.0f, MTL_BLUE_SHINY,
			g_drawImposter[0]);
		DrawSphereOrbit(modelMatrix, glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.6f, 0.8f, 0.0f),
			20.0f, g_sphereTimer.GetAlpha(), 2.0f, MTL_DULL_GREY, g_drawImposter[1]);
		DrawSphereOrbit(modelMatrix, glm::vec3(-10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			10.0f, g_sphereTimer.GetAlpha(), 1.0f, MTL_BLACK_SHINY, g_drawImposter[2]);
		DrawSphereOrbit(modelMatrix, glm::vec3(10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			10.0f, g_sphereTimer.GetAlpha() * 2.0f, 1.0f, MTL_GOLD_METAL, g_drawImposter[3]);

		if(g_bDrawLights)
		{
			glutil::PushStack push(modelMatrix);

			modelMatrix.Translate(glm::vec3(CalcLightPosition()));
			modelMatrix.Scale(0.5f);

			glUseProgram(g_Unlit.theProgram);
			glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));

			glm::vec4 lightColor(1.0f);
			glUniform4fv(g_Unlit.objectColorUnif, 1, glm::value_ptr(lightColor));
			g_pCubeMesh->Render("flat");
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
			g_pCubeMesh->Render("flat");
			glDepthMask(GL_TRUE);
			glEnable(GL_DEPTH_TEST);
			glUniform4f(g_Unlit.objectColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
			g_pCubeMesh->Render("flat");
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

//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		delete g_pPlaneMesh;
		delete g_pSphereMesh;
		g_pPlaneMesh = NULL;
		g_pSphereMesh = NULL;
		glutLeaveMainLoop();
		return;

	case 'p': g_sphereTimer.TogglePause(); break;
	case '-': g_sphereTimer.Rewind(0.5f); break;
	case '=': g_sphereTimer.Fastforward(0.5f); break;
	case 't': g_bDrawCameraPos = !g_bDrawCameraPos; break;
	case 'g': g_bDrawLights = !g_bDrawLights; break;

	case '1': g_drawImposter[0] = !g_drawImposter[0]; break;
	case '2': g_drawImposter[1] = !g_drawImposter[1]; break;
	case '3': g_drawImposter[2] = !g_drawImposter[2]; break;
	case '4': g_drawImposter[3] = !g_drawImposter[3]; break;

	case 'l': g_currImpostor = IMP_BASIC; break;
	case 'j': g_currImpostor = IMP_PERSPECTIVE; break;
	case 'h': g_currImpostor = IMP_DEPTH; break;
	}

	g_viewPole.CharPress(key);
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
