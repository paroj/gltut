#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <glimg/glimg.h>
#include <GL/freeglut.h>
#include <glutil/MatrixStack.h>
#include <glutil/MousePoles.h>
#include "../framework/framework_all.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

const float g_fzNear = 0.1f;
const float g_fzFar = 100.0f;

const int g_projectionBlockIndex = 0;
const int g_lightBlockIndex = 1;

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

GLuint g_projectionUniformBuffer = 0;
GLuint g_lightUniformBuffer = 0;

/*
const int NUM_SAMPLERS = 2;
GLuint g_samplers[NUM_SAMPLERS];

void CreateSamplers()
{
	glGenSamplers(NUM_SAMPLERS, &g_samplers[0]);

	for(int samplerIx = 0; samplerIx < NUM_SAMPLERS; samplerIx++)
	{
		glSamplerParameteri(g_samplers[samplerIx], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(g_samplers[samplerIx], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	glSamplerParameteri(g_samplers[0], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(g_samplers[0], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glSamplerParameteri(g_samplers[1], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glSamplerParameteri(g_samplers[1], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	glSamplerParameterfv(g_samplers[1], GL_TEXTURE_BORDER_COLOR, color);
}
*/

/*
struct TexDef { const char *filename; const char *name; };

TexDef g_texDefs[] =
{
	{"Flashlight.dds", "Flashlight"},
	{"PointsOfLight.dds", "Multiple Point Lights"},
	{"Bands.dds", "Light Bands"},
};

GLuint g_lightTextures[ARRAY_COUNT(g_texDefs)];
const int NUM_LIGHT_TEXTURES = ARRAY_COUNT(g_texDefs);
int g_currTextureIndex = 0;

void LoadTextures()
{
	try
	{
		for(int tex = 0; tex < NUM_LIGHT_TEXTURES; ++tex)
		{
			std::string filename(Framework::FindFileOrThrow(g_texDefs[tex].filename));

			std::auto_ptr<glimg::ImageSet> pImageSet(glimg::loaders::dds::LoadFromFile(filename.c_str()));
			g_lightTextures[tex] = glimg::CreateTexture(pImageSet.get(), 0);
		}
	}
	catch(std::exception &e)
	{
		printf("%s\n", e.what());
		throw;
	}
}
*/
glutil::ObjectData g_objectData =
{
	glm::vec3(0.0f, 1.0f, 2.0f),
	glm::fquat(1.0f, 0.0f, 0.0f, 0.0f),
};

glutil::ViewPole *g_pViewPole = NULL;
glutil::ObjectPole *g_pObjPole = NULL;

namespace
{
	void MouseMotion(int x, int y)
	{
		if(g_pViewPole)
		{
			Framework::ForwardMouseMotion(*g_pViewPole, x, y);
			Framework::ForwardMouseMotion(*g_pObjPole, x, y);
		}
	}

	void MouseButton(int button, int state, int x, int y)
	{
		if(g_pViewPole)
		{
			Framework::ForwardMouseButton(*g_pViewPole, button, state, x, y);
			Framework::ForwardMouseButton(*g_pObjPole, button, state, x, y);
		}
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		if(g_pViewPole)
		{
			Framework::ForwardMouseWheel(*g_pViewPole, wheel, direction, x, y);
		}
	}
}

Framework::Scene *g_pScene = NULL;
std::vector<Framework::NodeRef> g_nodes;
Framework::Timer g_timer(Framework::Timer::TT_LOOP, 10.0f);

Framework::UniformIntBinder g_lightNumBinder;

GLint g_unlitModelToCameraMatrixUnif;
GLint g_unlitObjectColorUnif;
GLuint g_unlitProg;
Framework::Mesh *g_pSphereMesh = NULL;
Framework::NodeRef g_bumpMapNode;
Framework::NodeRef g_highPolyNode;



void LoadAndSetupScene()
{
	std::auto_ptr<Framework::Scene> pScene(new Framework::Scene("bump_square_scene.xml"));

	std::vector<Framework::NodeRef> nodes = pScene->GetAllNodes();

	AssociateUniformWithNodes(nodes, g_lightNumBinder, "numberOfLights");
	SetStateBinderWithNodes(nodes, g_lightNumBinder);

	Framework::NodeRef bumpMapNode = pScene->FindNode("object");
	Framework::NodeRef highPolyNode = pScene->FindNode("high_poly");
	
	GLuint unlit = pScene->FindProgram("p_unlit");
	Framework::Mesh *pSphereMesh = pScene->FindMesh("m_sphere");

	std::auto_ptr<glutil::ViewPole> pViewPole(pScene->CreateCamera("c_main", glutil::MB_LEFT_BTN));
	if(pViewPole.get() == NULL)
		throw std::runtime_error("Could not find the main camera in the scene.");

	std::auto_ptr<glutil::ObjectPole> pObjPole(new glutil::ObjectPole(g_objectData, 0.36f,
		glutil::MB_RIGHT_BTN, pViewPole.get()));

	//No more things that can throw.
	g_unlitProg = unlit;
	g_unlitModelToCameraMatrixUnif = glGetUniformLocation(unlit, "modelToCameraMatrix");
	g_unlitObjectColorUnif = glGetUniformLocation(unlit, "objectColor");
	g_bumpMapNode = bumpMapNode;
	g_highPolyNode = highPolyNode;

	std::swap(nodes, g_nodes);
	nodes.clear();	//If something was there already, delete it.

	std::swap(pSphereMesh, g_pSphereMesh);

	glutil::ViewPole *pTemp = g_pViewPole;
	g_pViewPole = pViewPole.release();
	pViewPole.reset(pTemp);		//If something was there already, delete it.

	glutil::ObjectPole *pTempObj = g_pObjPole;
	g_pObjPole = pObjPole.release();
	pObjPole.reset(pTempObj);		//If something was there already, delete it.

	Framework::Scene *pOldScene = g_pScene;
	g_pScene = pScene.release();
	pScene.reset(pOldScene);	//If something was there already, delete it.
}

struct PerLight
{
	glm::vec4 cameraSpaceLightPos;
	glm::vec4 lightIntensity;
};

const int MAX_NUMBER_OF_LIGHTS = 4;

struct LightBlock
{
	glm::vec4 ambientIntensity;
	float lightAttenuation;
	float maxIntensity;
	float padding[2];
	PerLight lights[MAX_NUMBER_OF_LIGHTS];
};


//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
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
	glEnable(GL_FRAMEBUFFER_SRGB);

	//Setup our Uniform Buffers
	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_STREAM_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_projectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

//	CreateSamplers();
//	LoadTextures();

	try
	{
		LoadAndSetupScene();
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}

	glGenBuffers(1, &g_lightUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBlock), NULL, GL_STREAM_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_lightBlockIndex, g_lightUniformBuffer,
		0, sizeof(LightBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

using Framework::Timer;

// int g_currSampler = 0;

bool g_bDrawCameraPos = false;
bool g_bDrawLightPos = true;
bool g_bLongLightRange = false;
bool g_bDrawBumpmap = true;

int g_displayWidth = 500;
int g_displayHeight = 500;

inline glm::vec4 GetLightOffset()
{
	const glm::vec4 g_lightOffsetShort = glm::vec4(-2.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 g_lightOffsetLong = glm::vec4(-4.0f, 0.0f, 0.0f, 1.0f);

	return g_bLongLightRange ? g_lightOffsetLong : g_lightOffsetShort;
}

void BuildLights( const glm::mat4 &camMatrix )
{
	LightBlock lightData;
	lightData.ambientIntensity = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	lightData.lightAttenuation = 1.0f / (30.0f * 30.0f);
	lightData.maxIntensity = 4.0f;
	lightData.lights[0].lightIntensity = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	lightData.lights[0].cameraSpaceLightPos = camMatrix *
		glm::normalize(glm::vec4(-0.2f, 0.5f, 0.5f, 0.0f));

	lightData.lights[1].lightIntensity = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);

	if(g_pObjPole)
	{
		lightData.lights[1].cameraSpaceLightPos = camMatrix * g_pObjPole->CalcMatrix() *
			GetLightOffset();
	}
	else
	{
		lightData.lights[1].cameraSpaceLightPos = camMatrix *
			glm::vec4(5.0f, 6.0f, 0.5f, 1.0f);
	}

	g_lightNumBinder.SetValue(2);

	glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBlock), &lightData, GL_STREAM_DRAW);
}

std::string GetRenderName()
{
	if(g_bDrawBumpmap)
		return "bump_regular";
	else
		return "high_regular";
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	if(!g_pScene)
		return;

	g_timer.Update();

	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const glm::mat4 &cameraMatrix = g_pViewPole->CalcMatrix();

	glutil::MatrixStack modelMatrix;
	modelMatrix *= cameraMatrix;

	BuildLights(cameraMatrix);

	{
		glViewport(0, 0, (GLsizei)g_displayWidth, (GLsizei)g_displayHeight);
		glutil::MatrixStack persMatrix;
		persMatrix.Perspective(60.0f, (g_displayWidth / (float)g_displayHeight), g_fzNear, g_fzFar);

		ProjectionBlock projData;
		projData.cameraToClipMatrix = persMatrix.Top();

		glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), &projData, GL_STREAM_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	{
		glm::mat4 temp(
			glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec4(1.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		g_bumpMapNode.SetNodePreTransform(temp);
		g_highPolyNode.SetNodePreTransform(temp);
	}

	g_pScene->Render(GetRenderName(), modelMatrix.Top());

	if(g_pObjPole && g_bDrawLightPos)
	{
		glutil::PushStack stackPush(modelMatrix);
		modelMatrix.ApplyMatrix(g_pObjPole->CalcMatrix());
		modelMatrix.Translate(glm::vec3(GetLightOffset()));
		modelMatrix.Scale(0.125f);

		glUseProgram(g_unlitProg);
		glUniformMatrix4fv(g_unlitModelToCameraMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(modelMatrix.Top()));
		glUniform4f(g_unlitObjectColorUnif, 0.01f, 0.01f, 0.01f, 1.0f);
		g_pSphereMesh->Render("flat");
	}

	if(g_bDrawCameraPos)
	{
		//Draw lookat point.
		glutil::PushStack stackPush(modelMatrix);
		modelMatrix.SetIdentity();
		modelMatrix.Translate(glm::vec3(0.0f, 0.0f, -g_pViewPole->GetView().radius));
		modelMatrix.Scale(0.125f);

		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glUseProgram(g_unlitProg);
		glUniformMatrix4fv(g_unlitModelToCameraMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(modelMatrix.Top()));
		glUniform4f(g_unlitObjectColorUnif, 0.25f, 0.25f, 0.25f, 1.0f);
		g_pSphereMesh->Render("flat");
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glUniform4f(g_unlitObjectColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
		g_pSphereMesh->Render("flat");
	}

    glutPostRedisplay();
	glutSwapBuffers();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	g_displayWidth = w;
	g_displayHeight = h;
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
		delete g_pScene;
		g_pScene = NULL;
		glutLeaveMainLoop();
		return;
	case 32:
		g_bDrawBumpmap = !g_bDrawBumpmap;
		break;
	case 't':
		g_bDrawCameraPos = !g_bDrawCameraPos;
		break;
	case 'g':
		g_bDrawLightPos = !g_bDrawLightPos;
		break;
	case 'i':
		g_bLongLightRange = !g_bLongLightRange;
		break;
	case 'p':
		g_timer.TogglePause();
		break;
	case '\r': //Enter key.
		{
			try
			{
				LoadAndSetupScene();
			}
			catch(std::exception &except)
			{
				printf("Failed to reload, due to: %s\n", except.what());
				return;
			}
		}
		break;
	}

	if(g_pViewPole)
	{
		g_pViewPole->CharPress(key);
		g_pObjPole->CharPress(key);
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height)
{
	g_displayWidth = width;
	g_displayHeight = height;
	return displayMode | GLUT_SRGB;
}

