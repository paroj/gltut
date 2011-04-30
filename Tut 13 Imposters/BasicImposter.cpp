#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <glloader/gl_3_3_comp.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MatrixStack.h"
#include "../framework/MousePole.h"
#include "../framework/ObjectPole.h"
#include "../framework/UniformBlockArray.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	GLuint modelToCameraMatrixUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_litMeshProg;
ProgramData g_litImposterProg;
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

	glUniformBlockBinding(data.theProgram, materialBlock, g_materialBlockIndex);
	glUniformBlockBinding(data.theProgram, lightBlock, g_lightBlockIndex);
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	return data;
}

void InitializePrograms()
{
	g_litMeshProg = LoadLitProgram("PN.vert", "Lighting.frag");

	g_Unlit = LoadUnlitProgram("Unlit.vert", "Unlit.frag");
}

Framework::RadiusDef radiusDef = {5.0f, 3.0f, 200.0f, 1.5f, 0.5f};
glm::vec3 objectCenter = glm::vec3(0.0f, 10.0f, 0.0f);

Framework::MousePole g_mousePole(objectCenter, radiusDef);
Framework::ObjectPole g_objectPole(objectCenter, &g_mousePole);

namespace
{
	void MouseMotion(int x, int y)
	{
		g_mousePole.GLUTMouseMove(glm::ivec2(x, y));
		g_objectPole.GLUTMouseMove(glm::ivec2(x, y));
		glutPostRedisplay();
	}

	void MouseButton(int button, int state, int x, int y)
	{
		g_mousePole.GLUTMouseButton(button, state, glm::ivec2(x, y));
		g_objectPole.GLUTMouseButton(button, state, glm::ivec2(x, y));
		glutPostRedisplay();
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		g_mousePole.GLUTMouseWheel(direction, glm::ivec2(x, y));
		g_objectPole.GLUTMouseWheel(direction, glm::ivec2(x, y));
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

const int NUMBER_OF_LIGHTS = 1;

struct LightBlock
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float maxIntensity;
	float gamma;
	float padding;
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

GLuint g_lightUniformBuffer = 0;
GLuint g_projectionUniformBuffer = 0;
GLuint g_materialUniformBuffer = 0;

int g_materialBlockOffset = 0;

void CreateMaterials()
{
	Framework::UniformBlockArray<MaterialBlock, 1> ubArray;
	g_materialBlockOffset = ubArray.GetArrayOffset();

	MaterialBlock mtl;
	mtl.diffuseColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.specularColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	mtl.specularShininess = 0.6f;
	ubArray[0] = mtl;

	g_materialUniformBuffer = ubArray.CreateBufferObject();
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pPlaneMesh = new Framework::Mesh("LargePlane.xml");
		g_pSphereMesh = new Framework::Mesh("UnitSphere.xml");
	}
	catch(std::exception &except)
	{
		printf(except.what());
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

	CreateMaterials();
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.

void display()
{
	glClearColor(0.5f, 1.0f, 0.5f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pPlaneMesh && g_pSphereMesh)
	{
		Framework::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_mousePole.CalcMatrix());
		const glm::mat4 &worldToCamMat = modelMatrix.Top();

		LightBlock lightData;

		lightData.ambientIntensity = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		lightData.lightAttenuation = 25.0f;
		lightData.maxIntensity = 1.0f;
		lightData.gamma = 2.2f;

		lightData.lights[0].cameraSpaceLightPos = worldToCamMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		lightData.lights[0].lightIntensity = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);

		glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightData), &lightData);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);


		{
			glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, g_materialUniformBuffer,
				0 * g_materialBlockOffset, sizeof(MaterialBlock));

			glm::mat3 normMatrix(modelMatrix.Top());
			normMatrix = glm::transpose(glm::inverse(normMatrix));

			glUseProgram(g_litMeshProg.theProgram);
			glUniformMatrix4fv(g_litMeshProg.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));
			glUniformMatrix3fv(g_litMeshProg.normalModelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(normMatrix));

			g_pPlaneMesh->Render();

			glUseProgram(0);
			glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, 0, 0, 0);
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
	switch (key)
	{
	case 27:
		delete g_pPlaneMesh;
		delete g_pSphereMesh;
		g_pPlaneMesh = NULL;
		g_pSphereMesh = NULL;
		glutLeaveMainLoop();
		break;

	}

	glutPostRedisplay();
	g_mousePole.GLUTKeyOffset(key, 5.0f, 1.0f);
}

