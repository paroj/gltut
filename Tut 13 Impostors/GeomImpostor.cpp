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
};

struct UnlitProgData
{
	GLuint theProgram;

	GLuint objectColorUnif;
	GLuint modelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramMeshData g_litMeshProg;
ProgramImposData g_litImpProg;
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

ProgramImposData LoadLitImposProgram(const std::string &strVertexShader,
									 const std::string &strGeometryShader,
									 const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_GEOMETRY_SHADER, strGeometryShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramImposData data;
	data.theProgram = Framework::CreateProgram(shaderList);

	GLuint materialBlock = glGetUniformBlockIndex(data.theProgram, "Material");
	GLuint lightBlock = glGetUniformBlockIndex(data.theProgram, "Light");
	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");

	glUniformBlockBinding(data.theProgram, materialBlock, g_materialBlockIndex);
	glUniformBlockBinding(data.theProgram, lightBlock, g_lightBlockIndex);
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

void InitializePrograms()
{
	g_litMeshProg = LoadLitMeshProgram("PN.vert", "Lighting.frag");

	g_litImpProg = LoadLitImposProgram("GeomImpostor.vert", "GeomImpostor.geom",
		"GeomImpostor.frag");

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

struct MaterialEntry
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
GLuint g_materialArrayUniformBuffer = 0;
GLuint g_materialTerrainUniformBuffer = 0;

const int NUMBER_OF_SPHERES = 4;

void CreateMaterials()
{
	std::vector<MaterialEntry> ubArray(NUMBER_OF_SPHERES);

	ubArray[0].diffuseColor = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f);
	ubArray[0].specularColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	ubArray[0].specularShininess = 0.1f;

	ubArray[1].diffuseColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	ubArray[1].specularColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	ubArray[1].specularShininess = 0.8f;

	ubArray[2].diffuseColor = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
	ubArray[2].specularColor = glm::vec4(0.95f, 0.95f, 0.95f, 1.0f);
	ubArray[2].specularShininess = 0.3f;

	ubArray[3].diffuseColor = glm::vec4(0.803f, 0.709f, 0.15f, 1.0f);
	ubArray[3].specularColor = glm::vec4(0.803f, 0.709f, 0.15f, 1.0f) * 0.75;
	ubArray[3].specularShininess = 0.18f;

	glGenBuffers(1, &g_materialArrayUniformBuffer);
	glGenBuffers(1, &g_materialTerrainUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_materialArrayUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialEntry) * ubArray.size(), &ubArray[0], GL_STATIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, g_materialTerrainUniformBuffer);
	MaterialEntry mtl;
	mtl.diffuseColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.specularColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.specularShininess = 0.6f;
	glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialEntry), &mtl, GL_STATIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint g_imposterVAO;
GLuint g_imposterVBO;

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

	glGenBuffers(1, &g_imposterVBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_imposterVBO);
	glBufferData(GL_ARRAY_BUFFER, NUMBER_OF_SPHERES * 4 * sizeof(float), NULL, GL_STREAM_DRAW);

	glGenVertexArrays(1, &g_imposterVAO);
	glBindVertexArray(g_imposterVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 16, (void*)(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 16, (void*)(12));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_PROGRAM_POINT_SIZE);

	CreateMaterials();
}

glm::vec3 GetSphereOrbitPos(glutil::MatrixStack &modelMatrix,
							const glm::vec3 &orbitCenter, const glm::vec3 &orbitAxis,
							float orbitRadius, float orbitAlpha)
{
	glutil::PushStack push(modelMatrix);

	modelMatrix.Translate(orbitCenter);
	modelMatrix.Rotate(orbitAxis, 360.0f * orbitAlpha);

	glm::vec3 offsetDir = glm::cross(orbitAxis, glm::vec3(0.0f, 1.0f, 0.0f));
	if(glm::length(offsetDir) < 0.001f)
		offsetDir = glm::cross(orbitAxis, glm::vec3(1.0f, 0.0f, 0.0f));

	offsetDir = glm::normalize(offsetDir);

	modelMatrix.Translate(offsetDir * orbitRadius);

	return glm::vec3(modelMatrix.Top() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
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

struct VertexData
{
	glm::vec3 cameraPosition;
	float sphereRadius;
};

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
			glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, g_materialTerrainUniformBuffer,
				0, sizeof(MaterialEntry));

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

		{
			VertexData posSizeArray[NUMBER_OF_SPHERES];

			posSizeArray[0].cameraPosition = glm::vec3(worldToCamMat * glm::vec4(0.0f, 10.0f, 0.0f, 1.0f));
			posSizeArray[0].sphereRadius = 4.0f;

			posSizeArray[1].cameraPosition = GetSphereOrbitPos(modelMatrix,
				glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.6f, 0.8f, 0.0f), 20.0f,
				g_sphereTimer.GetAlpha());
			posSizeArray[1].sphereRadius = 2.0f;

			posSizeArray[2].cameraPosition = GetSphereOrbitPos(modelMatrix,
				glm::vec3(-10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
				10.0f, g_sphereTimer.GetAlpha());
			posSizeArray[2].sphereRadius = 1.0f;

			posSizeArray[3].cameraPosition = GetSphereOrbitPos(modelMatrix,
				glm::vec3(10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
				10.0f, g_sphereTimer.GetAlpha() * 2.0f);
			posSizeArray[3].sphereRadius = 1.0f;

			glBindBuffer(GL_ARRAY_BUFFER, g_imposterVBO);
			glBufferData(GL_ARRAY_BUFFER, NUMBER_OF_SPHERES * sizeof(VertexData), posSizeArray,
				GL_STREAM_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		{
			glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, g_materialArrayUniformBuffer,
				0, sizeof(MaterialEntry) * NUMBER_OF_SPHERES);

			glUseProgram(g_litImpProg.theProgram);
			glBindVertexArray(g_imposterVAO);
			glDrawArrays(GL_POINTS, 0, NUMBER_OF_SPHERES);
			glBindVertexArray(0);
			glUseProgram(0);

			glBindBufferBase(GL_UNIFORM_BUFFER, g_materialBlockIndex, 0);
		}

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
	}

	g_viewPole.CharPress(key);
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
