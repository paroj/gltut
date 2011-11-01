#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <memory>
#include <glimg/glimg.h>
#include <glimg/TextureGenerator.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glutil/MatrixStack.h>
#include <glutil/MousePoles.h>
#include <glutil/Shader.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../framework/Timer.h"
#include "../framework/UniformBlockArray.h"
#include "../framework/directories.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

struct ProgramData
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;
};

struct UnlitProgData
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;
	GLuint objectColorUnif;
};

float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData g_progStandard;
UnlitProgData g_progUnlit;

const int g_projectionBlockIndex = 0;
const int g_lightBlockIndex = 0;
const int g_colorTexUnit = 0;

ProgramData LoadProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");

	GLuint projectionBlock = glGetUniformBlockIndex(data.theProgram, "Projection");
	glUniformBlockBinding(data.theProgram, projectionBlock, g_projectionBlockIndex);

	GLuint colorTextureUnif = glGetUniformLocation(data.theProgram, "diffuseColorTex");
	glUseProgram(data.theProgram);
	glUniform1i(colorTextureUnif, g_colorTexUnit);
	glUseProgram(0);

	return data;
}

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

void InitializePrograms()
{
	g_progStandard = LoadProgram("PNT.vert", "litTexture.frag");
	g_progUnlit = LoadUnlitProgram("Unlit.vert", "Unlit.frag");
}

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

GLuint g_projectionUniformBuffer = 0;
GLuint g_linearTexture = 0;
// GLuint g_gammaTexture = 0;

const int NUM_SAMPLERS = 2;
GLuint g_samplers[NUM_SAMPLERS];

void CreateSamplers()
{
	glGenSamplers(NUM_SAMPLERS, &g_samplers[0]);

	for(int samplerIx = 0; samplerIx < NUM_SAMPLERS; samplerIx++)
	{
		glSamplerParameteri(g_samplers[samplerIx], GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(g_samplers[samplerIx], GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	//Linear mipmap linear
	glSamplerParameteri(g_samplers[0], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_samplers[0], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Max anisotropic
	GLfloat maxAniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);

	glSamplerParameteri(g_samplers[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(g_samplers[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(g_samplers[1], GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
}

void LoadTextures()
{
	try
	{
		std::string filename(Framework::FindFileOrThrow("terrain_tex.dds"));

		std::auto_ptr<glimg::ImageSet> pImageSet(glimg::loaders::dds::LoadFromFile(filename.c_str()));

		glGenTextures(1, &g_linearTexture);
		glBindTexture(GL_TEXTURE_2D, g_linearTexture);

		glimg::OpenGLPixelTransferParams xfer = glimg::GetUploadFormatType(pImageSet->GetFormat(), 0);

		for(int mipmapLevel = 0; mipmapLevel < pImageSet->GetMipmapCount(); mipmapLevel++)
		{
			glimg::SingleImage image = pImageSet->GetImage(mipmapLevel, 0, 0);
			glimg::Dimensions dims = image.GetDimensions();

			glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_SRGB8_ALPHA8, dims.width, dims.height, 0,
				xfer.format, xfer.type, image.GetImageData());
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, pImageSet->GetMipmapCount() - 1);

		glBindTexture(GL_TEXTURE_2D, 0);
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
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::fquat(0.924f, 0.384f, 0.0f, 0.0f),
	30.0f,
	0.0f
};

glutil::ViewScale g_initialViewScale =
{
	5.0f,
	90.0f,
	2.0f,
	0.5f,
	4.0f,
	1.0f,
	90.0f/250.0f
};

glutil::ViewPole g_viewPole(g_initialView, g_initialViewScale, glutil::MB_LEFT_BTN);


namespace
{
	int calc_glut_modifiers()
	{
		int ret = 0;

		int modifiers = glutGetModifiers();
		if(modifiers & GLUT_ACTIVE_SHIFT)
			ret |= glutil::MM_KEY_SHIFT;
		if(modifiers & GLUT_ACTIVE_CTRL)
			ret |= glutil::MM_KEY_CTRL;
		if(modifiers & GLUT_ACTIVE_ALT)
			ret |= glutil::MM_KEY_ALT;

		return ret;
	}

	void MouseMotion(int x, int y)
	{
		g_viewPole.MouseMove(glm::ivec2(x, y));
		glutPostRedisplay();
	}


	void MouseButton(int button, int state, int x, int y)
	{
		int modifiers = calc_glut_modifiers();

		glm::ivec2 mouseLoc = glm::ivec2(x, y);

		glutil::MouseButtons eButton;

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			eButton = glutil::MB_LEFT_BTN;
			break;
		case GLUT_MIDDLE_BUTTON:
			eButton = glutil::MB_MIDDLE_BTN;
			break;
		case GLUT_RIGHT_BUTTON:
			eButton = glutil::MB_RIGHT_BTN;
			break;
#ifdef LOAD_X11
			//Linux Mouse wheel support
		case 3:
			{
				g_viewPole.MouseWheel(1, modifiers, mouseLoc);
				return;
			}
		case 4:
			{
				g_viewPole.MouseWheel(-1, modifiers, mouseLoc);
				return;
			}
#endif
		default:
			return;
		}

		g_viewPole.MouseClick(eButton, state == GLUT_DOWN, modifiers, glm::ivec2(x, y));
		glutPostRedisplay();
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		g_viewPole.MouseWheel(direction, calc_glut_modifiers(), glm::ivec2(x, y));
		glutPostRedisplay();
	}
}

Framework::Mesh *g_pTerrain = NULL;
Framework::Mesh *g_pSphere = NULL;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	try
	{
		InitializePrograms();

		g_pTerrain = new Framework::Mesh("terrain.xml");
		g_pSphere = new Framework::Mesh("UnitSphere.xml");
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
	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_projectionBlockIndex, g_projectionUniformBuffer,
		0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	LoadTextures();
	CreateSamplers();
}

using Framework::Timer;

int g_currSampler = 0;

bool g_drawGammaProgram = false;
bool g_bDrawCameraPos = false;

bool g_useGammaDisplay = false;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(g_useGammaDisplay)
		glEnable(GL_FRAMEBUFFER_SRGB);
	else
		glDisable(GL_FRAMEBUFFER_SRGB);

	if(g_pSphere && g_pTerrain)
	{
		glutil::MatrixStack modelMatrix;

		modelMatrix.ApplyMatrix(g_viewPole.CalcMatrix());

		glutil::PushStack push(modelMatrix);
		modelMatrix.RotateX(-90.0f);

		glUseProgram(g_progStandard.theProgram);
		glUniformMatrix4fv(g_progStandard.modelToCameraMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(modelMatrix.Top()));

		glActiveTexture(GL_TEXTURE0 + g_colorTexUnit);
		glBindTexture(GL_TEXTURE_2D, g_linearTexture);
		glBindSampler(g_colorTexUnit, g_samplers[g_currSampler]);

		g_pTerrain->Render("lit-tex");

		glBindSampler(g_colorTexUnit, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glUseProgram(0);


		push.ResetStack();


		if(g_bDrawCameraPos)
		{
			//Draw lookat point.
			modelMatrix.SetIdentity();
			modelMatrix.Translate(glm::vec3(0.0f, 0.0f, -g_viewPole.GetView().radius));

			glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
			glUseProgram(g_progUnlit.theProgram);
			glUniformMatrix4fv(g_progUnlit.modelToCameraMatrixUnif, 1, GL_FALSE,
				glm::value_ptr(modelMatrix.Top()));
			glUniform4f(g_progUnlit.objectColorUnif, 0.25f, 0.25f, 0.25f, 1.0f);
			g_pSphere->Render("flat");
			glDepthMask(GL_TRUE);
			glEnable(GL_DEPTH_TEST);
			glUniform4f(g_progUnlit.objectColorUnif, 1.0f, 1.0f, 1.0f, 1.0f);
			g_pSphere->Render("flat");
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
	persMatrix.Perspective(60.0f, (h / (float)w), g_fzNear, g_fzFar);

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
		delete g_pSphere;
		delete g_pTerrain;
		g_pSphere = NULL;
		g_pTerrain = NULL;
		glutLeaveMainLoop();
		return;
	case 'a':
		g_drawGammaProgram = !g_drawGammaProgram;
		break;
	case 32:
		g_useGammaDisplay = !g_useGammaDisplay;
		break;
	case 't': g_bDrawCameraPos = !g_bDrawCameraPos; break;
	}

	if(('1' <= key) && (key <= '9'))
	{
		int number = key - '1';
		if(number < NUM_SAMPLERS)
		{
			g_currSampler = number;
		}
	}

	g_viewPole.CharPress(key);
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode | GLUT_SRGB;}
