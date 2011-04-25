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

	GLuint modelToCameraMatrixUnif;
	GLuint normalModelToCameraMatrixUnif;
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

	LM_DIFFUSE_SPECULAR,
	LM_DIFFUSE,

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

	{"PN.vert", "DiffuseSpecularMtl.frag"},
	{"PN.vert", "DiffuseOnlyMtl.frag"},
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
glm::vec3 objectCenter = glm::vec3(-59.5f, 4.0f, 65.0f);

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

//One for the ground, and one for each of the 5 objects.
const int MATERIAL_COUNT = 6;

void GetMaterials(std::vector<MaterialBlock> &materials)
{
	materials.resize(MATERIAL_COUNT);

	//Ground
	materials[0].diffuseColor = glm::vec4(1.0f);
	materials[0].specularColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	materials[0].specularShininess = 0.6f;

	//Tetrahedron
	materials[1].diffuseColor = glm::vec4(0.5f);
	materials[1].specularColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	materials[1].specularShininess = 0.05f;

	//Monolith
	materials[2].diffuseColor = glm::vec4(0.05f);
	materials[2].specularColor = glm::vec4(0.95f, 0.95f, 0.95f, 1.0f);
	materials[2].specularShininess = 0.4f;

	//Cube
	materials[3].diffuseColor = glm::vec4(0.5f);
	materials[3].specularColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	materials[3].specularShininess = 0.1f;

	//Cylinder
	materials[4].diffuseColor = glm::vec4(0.5f);
	materials[4].specularColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	materials[4].specularShininess = 0.6f;

	//Sphere
	materials[5].diffuseColor = glm::vec4(0.63f, 0.60f, 0.02f, 1.0f);
	materials[5].specularColor = glm::vec4(0.22f, 0.20f, 0.0f, 1.0f);
	materials[5].specularShininess = 0.3f;
}

GLuint g_lightUniformBuffer;
GLuint g_materialUniformBuffer;
GLuint g_projectionUniformBuffer;

GLuint g_sizeMaterialBlock = 0;

void GenerateMaterialBuffer()
{
	//Align the size of each MaterialBlock to the uniform buffer alignment.
	int uniformBufferAlignSize = 0;
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &uniformBufferAlignSize);

	g_sizeMaterialBlock = sizeof(MaterialBlock);
	g_sizeMaterialBlock += uniformBufferAlignSize -
		(g_sizeMaterialBlock % uniformBufferAlignSize);

	int sizeMaterialUniformBuffer = g_sizeMaterialBlock * MATERIAL_COUNT;

	std::vector<MaterialBlock> materials;
	GetMaterials(materials);
	assert(materials.size() == MATERIAL_COUNT);

	std::vector<GLubyte> mtlBuffer;
	mtlBuffer.resize(sizeMaterialUniformBuffer, 0);

	GLubyte *bufferPtr = &mtlBuffer[0];

	for(size_t mtl = 0; mtl < materials.size(); ++mtl)
		memcpy(bufferPtr + (mtl * g_sizeMaterialBlock), &materials[mtl], sizeof(MaterialBlock));

	glGenBuffers(1, &g_materialUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_materialUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeMaterialUniformBuffer, bufferPtr, GL_STATIC_DRAW);
}

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

Framework::Mesh *g_pTerrainMesh = NULL;
Framework::Mesh *g_pCubeMesh = NULL;
Framework::Mesh *g_pTetraMesh = NULL;
Framework::Mesh *g_pCylMesh = NULL;
Framework::Mesh *g_pSphereMesh = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pTerrainMesh = new Framework::Mesh("Ground.xml");
		g_pCubeMesh = new Framework::Mesh("UnitCube.xml");
		g_pTetraMesh = new Framework::Mesh("UnitTetrahedron.xml");
		g_pCylMesh = new Framework::Mesh("UnitCylinder.xml");
		g_pSphereMesh = new Framework::Mesh("UnitSphere.xml");
	}
	catch(std::exception &except)
	{
		printf(except.what());
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
	glBindBufferRange(GL_UNIFORM_BUFFER, g_iLightBlockIndex, g_lightUniformBuffer,
		0, sizeof(LightBlock));

	glBindBufferRange(GL_UNIFORM_BUFFER, g_iProjectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	GenerateMaterialBuffer();

}

bool g_bDrawCameraPos = false;
bool g_bDrawLights = true;

void DrawObject(const Framework::Mesh *pMesh, 
				const ProgramData &prog, int mtlIx,
				const Framework::MatrixStack &modelMatrix)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, g_iMaterialBlockIndex, g_materialUniformBuffer,
		mtlIx * g_sizeMaterialBlock, sizeof(MaterialBlock));

	glm::mat3 normMatrix(modelMatrix.Top());
	normMatrix = glm::transpose(glm::inverse(normMatrix));

	glUseProgram(prog.theProgram);
	glUniformMatrix4fv(prog.modelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(modelMatrix.Top()));

	glUniformMatrix3fv(prog.normalModelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(normMatrix));
	pMesh->Render();
	glUseProgram(0);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_iMaterialBlockIndex, 0, 0, 0);
}

void DrawObject(const Framework::Mesh *pMesh, const std::string &meshName, 
				const ProgramData &prog, int mtlIx,
				const Framework::MatrixStack &modelMatrix)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, g_iMaterialBlockIndex, g_materialUniformBuffer,
		mtlIx * g_sizeMaterialBlock, sizeof(MaterialBlock));

	glm::mat3 normMatrix(modelMatrix.Top());
	normMatrix = glm::transpose(glm::inverse(normMatrix));

	glUseProgram(prog.theProgram);
	glUniformMatrix4fv(prog.modelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(modelMatrix.Top()));

	glUniformMatrix3fv(prog.normalModelToCameraMatrixUnif, 1, GL_FALSE,
		glm::value_ptr(normMatrix));
	pMesh->Render(meshName);
	glUseProgram(0);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_iMaterialBlockIndex, 0, 0, 0);
}

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

	Framework::MatrixStack modelMatrix;
	modelMatrix.SetMatrix(g_mousePole.CalcMatrix());

	const glm::mat4 &worldToCamMat = modelMatrix.Top();
	LightBlock lightData = g_lights.GetLightPositions(worldToCamMat);

	glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightData), &lightData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	{
		Framework::MatrixStackPusher push(modelMatrix);

		//Render the ground plane.
		{
			Framework::MatrixStackPusher push(modelMatrix);
			modelMatrix.RotateX(-90);

			DrawObject(g_pTerrainMesh, g_Programs[LM_VERT_COLOR_DIFFUSE], 0,
				modelMatrix);
		}

		//Render the tetrahedron object.
		{
			Framework::MatrixStackPusher push(modelMatrix);
			modelMatrix.Translate(75.0f, 5.0f, 75.0f);
			modelMatrix.RotateY(360.0f * g_lights.GetTimerValue("tetra"));
			modelMatrix.Scale(10.0f, 10.0f, 10.0f);
			modelMatrix.Translate(0.0f, sqrtf(2.0f), 0.0f);
			modelMatrix.Rotate(glm::vec3(-0.707f, 0.0f, -0.707f), 54.735f);

			DrawObject(g_pTetraMesh, "lit-color", g_Programs[LM_VERT_COLOR_DIFFUSE_SPECULAR],
				1, modelMatrix);
		}

		//Render the monolith object.
		{
			Framework::MatrixStackPusher push(modelMatrix);
			modelMatrix.Translate(88.0f, 5.0f, -80.0f);
			modelMatrix.Scale(4.0f, 4.0f, 4.0f);
			modelMatrix.Scale(4.0f, 9.0f, 1.0f);
			modelMatrix.Translate(0.0f, 0.5f, 0.0f);

			DrawObject(g_pCubeMesh, "lit", g_Programs[LM_DIFFUSE_SPECULAR],
				2, modelMatrix);
		}

		//Render the cube object.
		{
			Framework::MatrixStackPusher push(modelMatrix);
			modelMatrix.Translate(-52.5f, 14.0f, 65.0f);
			modelMatrix.RotateZ(50.0f);
			modelMatrix.RotateY(-10.0f);
			modelMatrix.Scale(20.0f, 20.0f, 20.0f);

			DrawObject(g_pCubeMesh, "lit-color", g_Programs[LM_VERT_COLOR_DIFFUSE_SPECULAR],
				3, modelMatrix);
		}

		//Render the cylinder.
		{
			Framework::MatrixStackPusher push(modelMatrix);
			modelMatrix.Translate(-7.0f, 30.0f, -14.0f);
			modelMatrix.Scale(15.0f, 55.0f, 15.0f);
			modelMatrix.Translate(0.0f, 0.5f, 0.0f);

			DrawObject(g_pCylMesh, "lit-color", g_Programs[LM_VERT_COLOR_DIFFUSE_SPECULAR],
				4, modelMatrix);
		}

		//Render the sphere.
		{
			Framework::MatrixStackPusher push(modelMatrix);
			modelMatrix.Translate(-83.0f, 14.0f, -77.0f);
			modelMatrix.Scale(20.0f, 20.0f, 20.0f);

			DrawObject(g_pSphereMesh, "lit", g_Programs[LM_DIFFUSE_SPECULAR],
				5, modelMatrix);
		}

		//Render the sun
		{
			Framework::MatrixStackPusher push(modelMatrix);

			glm::vec3 sunlightDir(g_lights.GetSunlightDirection());
			modelMatrix.Translate(sunlightDir * 500.0f);
			modelMatrix.Scale(30.0f, 30.0f, 30.0f);

			glUseProgram(g_Unlit.theProgram);
			glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));

			glm::vec4 lightColor = g_lights.GetSunlightIntensity();
			glUniform4fv(g_Unlit.objectColorUnif, 1, glm::value_ptr(lightColor));
			g_pSphereMesh->Render("flat");
		}

		//Render the lights
		if(g_bDrawLights)
		{
			for(int light = 0; light < g_lights.GetNumberOfPointLights(); light++)
			{
				Framework::MatrixStackPusher push(modelMatrix);

				modelMatrix.Translate(g_lights.GetWorldLightPosition(light));

				glUseProgram(g_Unlit.theProgram);
				glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
					glm::value_ptr(modelMatrix.Top()));

				glm::vec4 lightColor = g_lights.GetPointLightIntensity(light);
				glUniform4fv(g_Unlit.objectColorUnif, 1, glm::value_ptr(lightColor));
				g_pCubeMesh->Render("flat");
			}
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
		delete g_pTerrainMesh;
		delete g_pCubeMesh;
		delete g_pTetraMesh;
		delete g_pCylMesh;
		delete g_pSphereMesh;
		g_pTerrainMesh = NULL;
		g_pCubeMesh = NULL;
		g_pTetraMesh = NULL;
		g_pCylMesh = NULL;
		g_pSphereMesh = NULL;
		glutLeaveMainLoop();
		break;
		
	case 'b': g_lights.TogglePause(g_eTimerMode); break;
	case '-': g_lights.RewindTime(g_eTimerMode, 1.0f); break;
	case '=': g_lights.FastForwardTime(g_eTimerMode, 1.0f); break;
	case 't': g_bDrawCameraPos = !g_bDrawCameraPos; break;
	case 'y': g_eTimerMode = TIMER_ALL; printf("All\n"); break;
	case 'h': g_eTimerMode = TIMER_SUN; printf("Sun\n"); break;
	case 'n': g_eTimerMode = TIMER_LIGHTS; printf("Lights\n"); break;

	case 'l': SetupDaytimeLighting(); break;
	case 'L': SetupNighttimeLighting(); break;

	case 32:
		printf("%f\n", g_lights.GetSunTime());
		break;
	}

	g_mousePole.GLUTKeyOffset(key, 5.0f, 1.0f);
}


