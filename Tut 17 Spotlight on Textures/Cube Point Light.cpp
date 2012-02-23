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

const float g_fzNear = 1.0f;
const float g_fzFar = 1000.0f;

const int g_projectionBlockIndex = 0;
const int g_lightBlockIndex = 1;
const int g_lightProjTexUnit = 3;

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

GLuint g_projectionUniformBuffer = 0;
GLuint g_lightUniformBuffer = 0;

const int NUM_SAMPLERS = 1;
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
	glSamplerParameteri(g_samplers[0], GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

struct TexDef { const char *filename; const char *name; };

TexDef g_texDefs[] =
{
	{"IrregularPoint.dds", "Irregular Point Light"},
	{"Planetarium.dds", "Planetarium"},
};

GLuint g_lightTextures[ARRAY_COUNT(g_texDefs)];
const int NUM_LIGHT_TEXTURES = ARRAY_COUNT(g_texDefs);
int g_currTextureIndex = 0;

void LoadTextures()
{
	try
	{
		glGenTextures(NUM_LIGHT_TEXTURES, g_lightTextures);

		for(int tex = 0; tex < NUM_LIGHT_TEXTURES; ++tex)
		{
			std::string filename(Framework::FindFileOrThrow(g_texDefs[tex].filename));
			std::auto_ptr<glimg::ImageSet> pImageSet(glimg::loaders::dds::LoadFromFile(filename.c_str()));

			glBindTexture(GL_TEXTURE_CUBE_MAP, g_lightTextures[tex]);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

			glimg::Dimensions dims = pImageSet->GetDimensions();
			GLenum imageFormat = (GLenum)glimg::GetInternalFormat(pImageSet->GetFormat(), 0);
			
			for(int face = 0; face < 6; ++face)
			{
				glimg::SingleImage img = pImageSet->GetImage(0, 0, face);
				glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
					0, imageFormat, dims.width, dims.height, 0,
					img.GetImageByteSize(), img.GetImageData());
			}

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
	catch(std::exception &e)
	{
		printf("%s\n", e.what());
		throw;
	}
}

////////////////////////////////
//View setup.
glutil::ViewData g_initialView =
{
	glm::vec3(0.0f, 0.0f, 10.0f),
 	glm::fquat(0.909845f, 0.16043f, -0.376867f, -0.0664516f),
	25.0f,
	0.0f
};

glutil::ViewScale g_initialViewScale =
{
	5.0f, 70.0f,	
	2.0f, 0.5f,
	2.0f, 0.5f,
	90.0f/250.0f
};

glutil::ObjectData g_initLightData =
{
	glm::vec3(0.0f, 0.0f, 10.0f),
	glm::fquat(1.0f, 0.0f, 0.0f, 0.0f),
};

glutil::ViewPole g_viewPole(g_initialView, g_initialViewScale, glutil::MB_LEFT_BTN);
glutil::ObjectPole g_lightPole(g_initLightData, 90.0f/250.0f, glutil::MB_RIGHT_BTN, &g_viewPole);

namespace
{
	void MouseMotion(int x, int y)
	{
		Framework::ForwardMouseMotion(g_viewPole, x, y);
		Framework::ForwardMouseMotion(g_lightPole, x, y);
	}

	void MouseButton(int button, int state, int x, int y)
	{
		Framework::ForwardMouseButton(g_viewPole, button, state, x, y);
		Framework::ForwardMouseButton(g_lightPole, button, state, x, y);
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		Framework::ForwardMouseWheel(g_viewPole, wheel, direction, x, y);
		Framework::ForwardMouseWheel(g_lightPole, wheel, direction, x, y);
	}
}

Framework::Scene *g_pScene = NULL;
std::vector<Framework::NodeRef> g_nodes;
Framework::Timer g_timer(Framework::Timer::TT_LOOP, 10.0f);

Framework::UniformIntBinder g_lightNumBinder;
Framework::TextureBinder g_stoneTexBinder;
Framework::UniformMat4Binder g_lightProjMatBinder;
Framework::UniformVec3Binder g_camLightPosBinder;

glm::fquat g_spinBarOrient;

GLint g_unlitModelToCameraMatrixUnif;
GLint g_unlitObjectColorUnif;
GLuint g_unlitProg;
Framework::Mesh *g_pSphereMesh = NULL;

GLint g_coloredModelToCameraMatrixUnif;
GLuint g_colroedProg;
Framework::Mesh *g_pAxesMesh = NULL;


void LoadAndSetupScene()
{
	std::auto_ptr<Framework::Scene> pScene(new Framework::Scene("projCube_scene.xml"));

	std::vector<Framework::NodeRef> nodes;
	nodes.push_back(pScene->FindNode("cube"));
	nodes.push_back(pScene->FindNode("rightBar"));
	nodes.push_back(pScene->FindNode("leaningBar"));
	nodes.push_back(pScene->FindNode("spinBar"));
	nodes.push_back(pScene->FindNode("diorama"));
	nodes.push_back(pScene->FindNode("floor"));

	AssociateUniformWithNodes(nodes, g_lightNumBinder, "numberOfLights");
	SetStateBinderWithNodes(nodes, g_lightNumBinder);
	AssociateUniformWithNodes(nodes, g_lightProjMatBinder, "cameraToLightProjMatrix");
	SetStateBinderWithNodes(nodes, g_lightProjMatBinder);
	AssociateUniformWithNodes(nodes, g_camLightPosBinder, "cameraSpaceProjLightPos");
	SetStateBinderWithNodes(nodes, g_camLightPosBinder);
	
	GLuint unlit = pScene->FindProgram("p_unlit");
	Framework::Mesh *pSphereMesh = pScene->FindMesh("m_sphere");

	GLuint colored = pScene->FindProgram("p_colored");
	Framework::Mesh *pAxesMesh = pScene->FindMesh("m_axes");

	//No more things that can throw.
	g_spinBarOrient = nodes[3].NodeGetOrient();
	g_unlitProg = unlit;
	g_unlitModelToCameraMatrixUnif = glGetUniformLocation(unlit, "modelToCameraMatrix");
	g_unlitObjectColorUnif = glGetUniformLocation(unlit, "objectColor");

	g_colroedProg = colored;
	g_coloredModelToCameraMatrixUnif = glGetUniformLocation(colored, "modelToCameraMatrix");

	std::swap(nodes, g_nodes);
	nodes.clear();	//If something was there already, delete it.

	std::swap(pSphereMesh, g_pSphereMesh);
	std::swap(pAxesMesh, g_pAxesMesh);

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

	CreateSamplers();
	LoadTextures();

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

int g_currSampler = 0;

const float g_lightFOVs[] = { 10.0f, 20.0f, 45.0f, 75.0f, 90.0f, 120.0f, 150.0f, 170.0f };
int g_currFOVIndex = 3;

bool g_bDrawCameraPos = false;
bool g_bShowOtherLights = true;

int g_displayWidth = 500;
int g_displayHeight = 500;

void BuildLights( const glm::mat4 &camMatrix )
{
	LightBlock lightData;
	lightData.ambientIntensity = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	lightData.lightAttenuation = 1.0f / (30.0f * 30.0f);
	lightData.maxIntensity = 2.0f;
	lightData.lights[0].lightIntensity = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	lightData.lights[0].cameraSpaceLightPos = camMatrix *
		glm::normalize(glm::vec4(-0.2f, 0.5f, 0.5f, 0.0f));
	lightData.lights[1].lightIntensity = glm::vec4(3.5f, 6.5f, 3.0f, 1.0f) * 0.5f;
	lightData.lights[1].cameraSpaceLightPos = camMatrix *
		glm::vec4(5.0f, 6.0f, 0.5f, 1.0f);

	if(g_bShowOtherLights)
		g_lightNumBinder.SetValue(2);
	else
		g_lightNumBinder.SetValue(0);

	glBindBuffer(GL_UNIFORM_BUFFER, g_lightUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBlock), &lightData, GL_STREAM_DRAW);
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

	const glm::mat4 &cameraMatrix = g_viewPole.CalcMatrix();
	const glm::mat4 &lightView = g_lightPole.CalcMatrix();

	glutil::MatrixStack modelMatrix;
	modelMatrix *= cameraMatrix;

	BuildLights(cameraMatrix);

	g_nodes[0].NodeSetOrient(glm::rotate(glm::fquat(),
		360.0f * g_timer.GetAlpha(), glm::vec3(0.0f, 1.0f, 0.0f)));

	g_nodes[3].NodeSetOrient(g_spinBarOrient * glm::rotate(glm::fquat(),
		360.0f * g_timer.GetAlpha(), glm::vec3(0.0f, 0.0f, 1.0f)));

	{
		glutil::MatrixStack persMatrix;
		persMatrix.Perspective(60.0f, (g_displayWidth / (float)g_displayHeight), g_fzNear, g_fzFar);

		ProjectionBlock projData;
		projData.cameraToClipMatrix = persMatrix.Top();

		glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), &projData, GL_STREAM_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	glActiveTexture(GL_TEXTURE0 + g_lightProjTexUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_lightTextures[g_currTextureIndex]);
	glBindSampler(g_lightProjTexUnit, g_samplers[g_currSampler]);

	{
		glutil::MatrixStack lightProjStack;
		lightProjStack.ApplyMatrix(glm::inverse(lightView));
		lightProjStack.ApplyMatrix(glm::inverse(cameraMatrix));

		g_lightProjMatBinder.SetValue(lightProjStack.Top());

		glm::vec4 worldLightPos = lightView[3];
		glm::vec3 lightPos = glm::vec3(cameraMatrix * worldLightPos);

		g_camLightPosBinder.SetValue(lightPos);
	}

	glViewport(0, 0, (GLsizei)g_displayWidth, (GLsizei)g_displayHeight);
	g_pScene->Render(modelMatrix.Top());

	{
		//Draw axes
		glutil::PushStack stackPush(modelMatrix);
		modelMatrix.ApplyMatrix(lightView);
		modelMatrix.Scale(15.0f);

		glUseProgram(g_colroedProg);
		glUniformMatrix4fv(g_coloredModelToCameraMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(modelMatrix.Top()));
		g_pAxesMesh->Render();
	}

	if(g_bDrawCameraPos)
	{
		//Draw lookat point.
		glutil::PushStack stackPush(modelMatrix);
		modelMatrix.SetIdentity();
		modelMatrix.Translate(glm::vec3(0.0f, 0.0f, -g_viewPole.GetView().radius));
		modelMatrix.Scale(0.5f);

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

	glActiveTexture(GL_TEXTURE0 + g_lightProjTexUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindSampler(g_lightProjTexUnit, 0);

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
		g_lightPole.Reset();
		break;
	case 't':
		g_bDrawCameraPos = !g_bDrawCameraPos;
		break;
	case 'g':
		g_bShowOtherLights = !g_bShowOtherLights;
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

	{
		int possibleIndex = (int)key - (int)'1';
		if((0 <= possibleIndex) && (possibleIndex < NUM_LIGHT_TEXTURES))
		{
			g_currTextureIndex = key - '1';
			printf("%s\n", g_texDefs[g_currTextureIndex].name);
		}
	}

	g_viewPole.CharPress(key);
	g_lightPole.CharPress(key);
}

unsigned int defaults(unsigned int displayMode, int &width, int &height)
{
	g_displayWidth = width;
	g_displayHeight = height;
	return displayMode | GLUT_SRGB;
}

