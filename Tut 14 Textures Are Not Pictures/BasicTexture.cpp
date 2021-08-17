#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glutil/glutil.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/MousePole.h"
#include "../framework/Timer.h"
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

ProgramData g_litShaderProg;
ProgramData g_litTextureProg;

UnlitProgData g_Unlit;

const int g_materialBlockIndex = 0;
const int g_lightBlockIndex = 1;
const int g_projectionBlockIndex = 2;

const int g_gaussTexUnit = 0;

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

ProgramData LoadStandardProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
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

	GLuint gaussianTextureUnif = glGetUniformLocation(data.theProgram, "gaussianTexture");
	glUseProgram(data.theProgram);
	glUniform1i(gaussianTextureUnif, g_gaussTexUnit);
	glUseProgram(0);

	return data;
}

void InitializePrograms()
{
	g_litShaderProg = LoadStandardProgram("PN.vert", "ShaderGaussian.frag");
	g_litTextureProg = LoadStandardProgram("PN.vert", "TextureGaussian.frag");

	g_Unlit = LoadUnlitProgram("Unlit.vert", "Unlit.frag");
}

///////////////////////////////////////////////
// View/Object Setup
glutil::ObjectData g_initialObjectData =
{
	glm::vec3(0.0f, 0.5f, 0.0f),
	glm::fquat(1.0f, 0.0f, 0.0f, 0.0f),
};

glutil::ViewData g_initialViewData =
{
	g_initialObjectData.position,
	glm::fquat(0.92387953f, 0.3826834f, 0.0f, 0.0f),
	10.0f,
	0.0f
};

glutil::ViewScale g_viewScale =
{
	1.5f, 70.0f,
	1.5f, 0.5f,
	0.0f, 0.0f,		//No camera movement.
	90.0f/250.0f
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

Framework::Mesh *g_pObjectMesh = NULL;
Framework::Mesh *g_pCubeMesh = NULL;

GLuint g_lightUniformBuffer = 0;
GLuint g_projectionUniformBuffer = 0;
GLuint g_materialUniformBuffer = 0;

const int NUM_GAUSS_TEXTURES = 4;
GLuint g_gaussTextures[NUM_GAUSS_TEXTURES];

GLuint g_gaussSampler = 0;

GLuint g_imposterVAO;
GLuint g_imposterVBO;

float g_specularShininess = 0.2f;

void BuildGaussianData(std::vector<GLubyte> &textureData,
					   int cosAngleResolution)
{
	textureData.resize(cosAngleResolution);

	std::vector<GLubyte>::iterator currIt = textureData.begin();
	for(int iCosAng = 0; iCosAng < cosAngleResolution; iCosAng++)
	{
		float cosAng = iCosAng / (float)(cosAngleResolution - 1);
		float angle = acosf(cosAng);
		float exponent = angle / g_specularShininess;
		exponent = -(exponent * exponent);
		float gaussianTerm = glm::exp(exponent);

		*currIt++ = (GLubyte)(gaussianTerm * 255.0f);
	}
}

GLuint CreateGaussianTexture(int cosAngleResolution)
{
	std::vector<GLubyte> textureData;
	BuildGaussianData(textureData, cosAngleResolution);

	GLuint gaussTexture;
	glGenTextures(1, &gaussTexture);
	glBindTexture(GL_TEXTURE_1D, gaussTexture);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R8, cosAngleResolution, 0,
		GL_RED, GL_UNSIGNED_BYTE, &textureData[0]);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAX_LEVEL, 0);
	glBindTexture(GL_TEXTURE_1D, 0);

	return gaussTexture;
}

int CalcCosAngResolution(int level)
{
	const int cosAngleStart = 64;
	return cosAngleStart * ((int)pow(2.0f, level));
}

void CreateGaussianTextures()
{
	for(int loop = 0; loop < NUM_GAUSS_TEXTURES; loop++)
	{
		int cosAngleResolution = CalcCosAngResolution(loop);
		g_gaussTextures[loop] = CreateGaussianTexture(cosAngleResolution);
	}

	glGenSamplers(1, &g_gaussSampler);
	glSamplerParameteri(g_gaussSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(g_gaussSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(g_gaussSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}


//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializePrograms();

	try
	{
		g_pObjectMesh = new Framework::Mesh("Infinity.xml");
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
	MaterialBlock mtl;
	mtl.diffuseColor = glm::vec4(1.0f, 0.673f, 0.043f, 1.0f);
	mtl.specularColor = glm::vec4(1.0f, 0.673f, 0.043f, 1.0f) * 0.4f;
	mtl.specularShininess = g_specularShininess;

	glGenBuffers(1, &g_materialUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_materialUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialBlock), &mtl, GL_STATIC_DRAW);

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

	glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, g_materialUniformBuffer,
		0, sizeof(MaterialBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	CreateGaussianTextures();
}

bool g_bDrawCameraPos = false;
bool g_bDrawLights = true;
bool g_bUseTexture = false;
int g_currTexture = 0;

Framework::Timer g_lightTimer = Framework::Timer(Framework::Timer::TT_LOOP, 6.0f);

float g_lightHeight = 1.0f;
float g_lightRadius = 3.0f;

glm::vec4 CalcLightPosition()
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f;

	float timeThroughLoop = g_lightTimer.GetAlpha();

	glm::vec4 ret(0.0f, g_lightHeight, 0.0f, 1.0f);

	ret.x = cosf(timeThroughLoop * fScale) * g_lightRadius;
	ret.z = sinf(timeThroughLoop * fScale) * g_lightRadius;

	return ret;
}

const float g_fHalfLightDistance = 25.0f;
const float g_fLightAttenuation = 1.0f / (g_fHalfLightDistance * g_fHalfLightDistance);

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	g_lightTimer.Update();

	glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(g_pObjectMesh && g_pCubeMesh)
	{
		glutil::MatrixStack modelMatrix;
		modelMatrix.SetMatrix(g_viewPole.CalcMatrix());
		const glm::mat4 &worldToCamMat = modelMatrix.Top();

		LightBlock lightData;

		lightData.ambientIntensity = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		lightData.lightAttenuation = g_fLightAttenuation;

		glm::vec3 globalLightDirection(0.707f, 0.707f, 0.0f);

		lightData.lights[0].cameraSpaceLightPos = worldToCamMat * glm::vec4(globalLightDirection, 0.0f);
		lightData.lights[0].lightIntensity = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);

		lightData.lights[1].cameraSpaceLightPos = worldToCamMat * CalcLightPosition();
		lightData.lights[1].lightIntensity = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);

		glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightData), &lightData);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		{
			glBindBufferRange(GL_UNIFORM_BUFFER, g_materialBlockIndex, g_materialUniformBuffer,
				0, sizeof(MaterialBlock));

			glutil::PushStack push(modelMatrix);
			modelMatrix.ApplyMatrix(g_objtPole.CalcMatrix());
			modelMatrix.Scale(2.0f);

			glm::mat3 normMatrix(modelMatrix.Top());
			normMatrix = glm::transpose(glm::inverse(normMatrix));

			ProgramData &prog = g_bUseTexture ? g_litTextureProg : g_litShaderProg;

			glUseProgram(prog.theProgram);
			glUniformMatrix4fv(prog.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));
			glUniformMatrix3fv(prog.normalModelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(normMatrix));

			glActiveTexture(GL_TEXTURE0 + g_gaussTexUnit);
			glBindTexture(GL_TEXTURE_1D, g_gaussTextures[g_currTexture]);
			glBindSampler(g_gaussTexUnit, g_gaussSampler);

			g_pObjectMesh->Render("lit");

			glBindSampler(g_gaussTexUnit, 0);
			glBindTexture(GL_TEXTURE_1D, 0);

			glUseProgram(0);
			glBindBufferBase(GL_UNIFORM_BUFFER, g_materialBlockIndex, 0);
		}

		if(g_bDrawLights)
		{
			glutil::PushStack push(modelMatrix);

			modelMatrix.Translate(glm::vec3(CalcLightPosition()));
			modelMatrix.Scale(0.25f);

			glUseProgram(g_Unlit.theProgram);
			glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));

			glm::vec4 lightColor(1.0f);
			glUniform4fv(g_Unlit.objectColorUnif, 1, glm::value_ptr(lightColor));
			g_pCubeMesh->Render("flat");

			push.ResetStack();

			modelMatrix.Translate(globalLightDirection * 100.0f);
			modelMatrix.Scale(5.0f);

			glUniformMatrix4fv(g_Unlit.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));
			g_pCubeMesh->Render("flat");

			glUseProgram(0);
		}

		if(g_bDrawCameraPos)
		{
			glutil::PushStack push(modelMatrix);

			modelMatrix.SetIdentity();
			modelMatrix.Translate(glm::vec3(0.0f, 0.0f, -g_viewPole.GetView().radius));
			modelMatrix.Scale(0.25f);

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
		delete g_pObjectMesh;
		delete g_pCubeMesh;
		g_pObjectMesh = NULL;
		g_pCubeMesh = NULL;
		glutLeaveMainLoop();
		return;

	case 'p': g_lightTimer.TogglePause(); break;
	case '-': g_lightTimer.Rewind(0.5f); break;
	case '=': g_lightTimer.Fastforward(0.5f); break;
	case 't': g_bDrawCameraPos = !g_bDrawCameraPos; break;
	case 'g': g_bDrawLights = !g_bDrawLights; break;
	case 32:
		g_bUseTexture = !g_bUseTexture;
		if(g_bUseTexture)
			printf("Texture\n");
		else
			printf("Shader\n");
		break;
	}

	if(('1' <= key) && (key <= '9'))
	{
		int number = key - '1';
		if(number < NUM_GAUSS_TEXTURES)
		{
			printf("Angle Resolution: %i\n", CalcCosAngResolution(number));
			g_currTexture = number;
		}
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
